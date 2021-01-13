//
// CONFIDENTIAL - FORD MOTOR COMPANY
//
// This is an unpublished work, which is a trade secret, created in
// 2020.  Ford Motor Company owns all rights to this work and intends
// to maintain it in confidence to preserve its trade secret status.
// Ford Motor Company reserves the right to protect this work as an
// unpublished copyrighted work in the event of an inadvertent or
// deliberate unauthorized publication.  Ford Motor Company also
// reserves its rights under the copyright laws to protect this work
// as a published work.  Those having access to this work may not copy
// it, use it, or disclose the information contained in it without
// the written authorization of Ford Motor Company.
//

#include <chrono>
#include <mutex>
#include <iostream>

#include <thread>
#include <condition_variable>

#include "soa-test-utils.hpp"
#include <include/soa/ipc/soa_connection_options_ipc.hpp>
#include <soa_provider.hpp>

namespace fnv {
namespace soa {
namespace gateway {
namespace functest {       

using namespace fnv::soa::framework;

const SoaClientEndpoint::SharedPtr DATA_ENDPOINT =  SoaClientEndpoint::createClientEndpointMqtt("SERVICES/DATA/UNIQUE_DATA_ENDPOINT");
const std::chrono::milliseconds TIMEOUT(1000);
const std::chrono::milliseconds ACTION_TIMEOUT(3000);

SoaErrorCode actionStatus;
std::mutex mut_msg;
std::condition_variable cv_msg;
std::mutex mut_init;
std::condition_variable cv_init;
bool isInitialized;
bool  isPublishCallbackCalled = false;


/**
 * Listener for Action Result
 * Use condition variable to communicate
 */
class PublishActionListenerBase : public  SoaActionResultListener< SoaPublishMessageContext>{
public:
    virtual void onActionCompleted(SoaErrorCode errorCode, std::shared_ptr<SoaPublishMessageContext> /*actionContext not used*/){
        {
            std::lock_guard<std::mutex> lock(mut_msg);
            actionStatus = errorCode;
            isPublishCallbackCalled = true;
        }
        cv_msg.notify_one();
    }
    ~PublishActionListenerBase() override = default;
};

/**
 * Listener for Connection Loss Status
 */
class ConnectionLostListenerBase : public SoaConnectionLostListener {
public:
    explicit ConnectionLostListenerBase(): SoaConnectionLostListener() {}
    virtual void onConnectionLost (const std::string& cause) override {
        std::cout << "onConnectionLost: " << cause << std::endl;
    }
    ~ConnectionLostListenerBase() override = default;
};

/**
 * Listener for Connection Status
 */
class ConnectionListenerBase : public  SoaConnectionListener {

public:
    explicit ConnectionListenerBase( ):
        SoaConnectionListener() {}
    virtual void onConnect( SoaErrorCode errorCode) override {
        if (errorCode ==  SoaErrorCode::NO_ERROR) {
            std::cout << "onConnect" << std::endl;
        } else if (errorCode ==  SoaErrorCode::NO_ERROR__GATEWAY_CONNECTED_ONLY) {
            std::cout << "NO_ERROR__GATEWAY_CONNECTED_ONLY" << std::endl;
        } else {
                std::cout << ("Connection Failed: " + SoaErrorCodeUtil::getString(errorCode) + "\n" );
            }
    }
    ~ConnectionListenerBase() override = default;
};

/**
 * Listener for provider Initialization Status
 * Use condition variable to communicate
 */
class InitializedProviderListenerBase : public SoaProvider::SoaInitializedProviderListener {
public:
    explicit InitializedProviderListenerBase( ):
    SoaProvider::SoaInitializedProviderListener() {}
    virtual void onInitialized( SoaErrorCode errorCode, const SoaProvider * provider) override {        
        if (errorCode ==  SoaErrorCode::NO_ERROR) {
            std::cout << "onInitialized" << std::endl;
            {
                std::lock_guard<std::mutex> lock(mut_init);
                isInitialized = true;
            }
            cv_init.notify_one();            
        } else {
            std::cout << ("Initialization Failed: " + SoaErrorCodeUtil::getString(errorCode) + "\n" );
        }
    }

    virtual void onDeinitialized(SoaErrorCode errorCode, const SoaProvider * provider) override {
        if (errorCode ==  SoaErrorCode::NO_ERROR) {
            std::cout << "onDeinitialized" << std::endl;
            std::lock_guard<std::mutex> lock(mut_init);
            isInitialized = false;
        } else {
            std::cout << ("Deinitialization Failed: " + SoaErrorCodeUtil::getString(errorCode) + "\n" );
        }
    }
    ~InitializedProviderListenerBase() override = default;
};

/**
 * Base test class is wrapped to securely deregister its listener
 * parents from the SoaResourceManager in most derived destructor
 * before any resources are destroyed.
 */
typedef  SoaListenerLifecycleHelper<
                                PublishActionListenerBase,
                                SoaActionResultListener< SoaPublishMessageContext>
                                > PublishActionListener;

typedef  SoaListenerLifecycleHelper<
                                ConnectionLostListenerBase,
                                SoaConnectionLostListener
                                > ConnectionLostListener;

typedef  SoaListenerLifecycleHelper<
                                ConnectionListenerBase,
                                SoaConnectionListener
                                > ConnectionListener;

typedef  SoaListenerLifecycleHelper<
                                InitializedProviderListenerBase,
                                SoaProvider::SoaInitializedProviderListener
                                > InitializedProviderListener;

const std::string TEST_PAYLOAD  = "TestDataPayloadViaSoaGateway";
int execute(uid_t uid) {
    
    if (uid != 0) {
        SoaTestUtils::changeUser(uid);
    }
    SoaConnectionOptionsIpc::SharedPtr m_connectionOptions;
    PublishActionListener actionListener;
    m_connectionOptions =  SoaConnectionOptionsIpc::createConnectionOptionsIpc();
    ConnectionListener connListener;
    m_connectionOptions->setConnectionListener(connListener);
    ConnectionLostListener connLostListener;
    m_connectionOptions->setConnectionLostListener(connLostListener);

    std::cout << "uid, gid = " << getuid() <<", " << getgid() << std::endl;

    //Create message manager
    SoaMessageManager::SharedPtr msgMan;

    msgMan = SoaMessageManager::createMessageManager(*m_connectionOptions);

    SoaProvider::SharedPtr provider =  SoaProvider::createSoaProvider(msgMan);
    msgMan->connectAsync();

    InitializedProviderListener initListener;
    SoaErrorCode status;
    status = provider->initializeAsync(initListener);

    if (status != SoaErrorCode::NO_ERROR){
        std::cout<<"async_publish_test: connect failed"<<std::endl;
        return 1;
    }

    {
        std::unique_lock<std::mutex> lock(mut_init);
        if (cv_init.wait_for(lock, ACTION_TIMEOUT, [&]{ return isInitialized; })) {      
            std::cout << "Initialized Successfully" << std::endl;
        } else {
            std::cout << "Initialize failed" << std::endl;
            return 1;
        }   
    }

    SoaMessage::SharedPtr data =  std::make_shared< SoaMessage>();
    int msg_num = 1;

    while (msg_num < 4) { 
        data->setPayload(TEST_PAYLOAD + std::to_string(msg_num));
        provider->publishMessageAsync(DATA_ENDPOINT, data, actionListener);
        {
            std::unique_lock<std::mutex> lock(mut_msg);
            if (cv_msg.wait_for(lock, TIMEOUT, [&]{ return  isPublishCallbackCalled; })) {
                std::cout<<"async_publish_test: publish action done"<<std::endl;
                isPublishCallbackCalled = false;
                if (actionStatus != SoaErrorCode::NO_ERROR) {
                    std::cout<<"async_publish_test: publish failed"<<std::endl;
                    return 1;
                }
            }
            else {
                std::cout<<"async_publish_test: publish action timeout"<<std::endl;
                return 1;              
            }
        }
        msg_num += 1;
        std::this_thread::sleep_for(TIMEOUT);
    }

    status = msgMan->disconnect();
    if (status !=  SoaErrorCode::NO_ERROR) {
        std::cout<<"async_publish_test: disconnect failed"<<std::endl;
        return 1;
    } else {
        std::cout<<"Disconnected Successfully"<<std::endl;
    }

    return 0;
}

}//namespace
}
}
}

/*
 * Test procedure
 * Provider publishes to data service endpoint "SERVICES/DATA/UNIQUE_DATA_ENDPOINT"
 * 1. Create a client that takes on user id passed in command line.
 * 2. Provider client connects to Soa gateway using non-blocking method
 * 3. Call initialize asynchronized
 * 4. Create a test payload and send the payload repeatedly
 */

int main(int argc, char *argv[]) {
    uid_t uid;
    if (argc == 2) {
        uid = atoi(argv[1]);
    } else {
        uid = 0;
    }
    return fnv::soa::gateway::functest::execute(uid);
}
