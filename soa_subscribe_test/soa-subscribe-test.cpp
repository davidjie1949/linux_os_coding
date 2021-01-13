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
#include "soa-test-utils.hpp"
#include <thread>
#include <condition_variable>
#include <iostream>

#include <soa_connection_options.hpp>
#include <soa_consumer.hpp>
#include <mutex>
#include <include/soa/ipc/soa_connection_options_ipc.hpp>


namespace fnv {
namespace soa {
namespace gateway {
namespace functest {

using namespace fnv::soa::framework;    

const SoaClientEndpoint::SharedPtr CONSUMER_ENDPOINT =  SoaClientEndpoint::createClientEndpointMqtt("SERVICES/RESPONSE/UNIQUE_CONSUMER_ENDPOINT");
const SoaClientEndpoint::SharedPtr CONSUMER_SDM_ENDPOINT =  SoaClientEndpoint::createClientEndpointMqtt("SERVICES/RESPONSE/DIFFERENT");
const SoaClientEndpoint::SharedPtr DATA_ENDPOINT =  SoaClientEndpoint::createClientEndpointMqtt("SERVICES/DATA/UNIQUE_DATA_ENDPOINT");
const std::chrono::milliseconds ACTION_TIMEOUT(1000);
const std::chrono::milliseconds MSG_TIMEOUT(20000);
const std::chrono::milliseconds INIT_TIMEOUT(3000);

SoaMessage::SharedPtr dataMsg;
SoaErrorCode actionStatus;
std::mutex mut_data;
std::condition_variable cv_data;
std::mutex mut_sub;
std::condition_variable cv_sub;
std::mutex mut_unsub;
std::condition_variable cv_unsub;
std::mutex mut_init;
std::condition_variable cv_init;
bool isInitialized;
bool isCallbackCalled = false;
bool isDataReceived = false;

/**
 * Listener for Soa data
 * Use condition variable to communicate
 */
class DataListenerBase : public SoaDataListener{
public:
    void onDataReceived(SoaMessage::SharedPtr data) override {
        {
            std::lock_guard<std::mutex> lock(mut_data);
            isDataReceived = true;
            dataMsg = data;
        }
        cv_data.notify_one();
    }
    ~DataListenerBase() override = default;
};

/**
 * Listener for Subscribe Action result
 * Use condition variable to communicate
 */
class SubscribeActionListenerBase : public SoaActionResultListener<SoaSubscribeToDataContext>{
    public:
    void onActionCompleted(SoaErrorCode errorCode, std::shared_ptr< SoaSubscribeToDataContext> /*actionContext not used*/) override {
        {
            std::lock_guard<std::mutex> lock(mut_sub);
            actionStatus = errorCode;
            isCallbackCalled = true;
        }
        cv_sub.notify_one();
    }
    ~SubscribeActionListenerBase() override = default;
};

/**
 * Listener for Unsubscribe Action result
 * Use condition variable to communicate
 */
class UnsubscribeActionListenerBase : public SoaActionResultListener<SoaUnsubscribeToDataContext>{
    public:
    void onActionCompleted(SoaErrorCode errorCode, std::shared_ptr<SoaUnsubscribeToDataContext> /*actionContext not used*/) override {
        {
            std::lock_guard<std::mutex> lock(mut_unsub);
            actionStatus = errorCode;
            isCallbackCalled = true;          
        }
        cv_unsub.notify_one();
    }
    ~UnsubscribeActionListenerBase() override = default;
};

/**
 * Listener for Connection Loss status
 */
class ConnectionLostListenerBase : public SoaConnectionLostListener{
    public:
    void onConnectionLost (const std::string& cause) override {
        std::cout << "Connection Lost: User set callback called! - Cause: " << cause << std::endl;
    }
    ~ConnectionLostListenerBase() override = default;
};

/**
 * Listener for Reconnection status
 */
class ReconnectionListenerBase : public SoaReconnectionListener{
    public:
    void onReconnect( SoaErrorCode errorCode) override {
        std::cout << "Reconnect: User set callback called! - Error: " << SoaErrorCodeUtil::getString(errorCode) << std::endl;
    }
    ~ReconnectionListenerBase() override = default;
};

/**
 * Listener for Connection status
 */
class ConnectionListenerBase : public SoaConnectionListener {
public:
    ConnectionListenerBase():
        SoaConnectionListener() {}
    void onConnect( SoaErrorCode errorCode) override {
        if (errorCode ==  SoaErrorCode::NO_ERROR) {
            std::cout << "onConnect" << std::endl;
        } else if (errorCode ==  SoaErrorCode::NO_ERROR__GATEWAY_CONNECTED_ONLY) {
            std::cout << "NO_ERROR__GATEWAY_CONNECTED_ONLY" << std::endl;
        } else {
            std::cout << "Connection Failed: " <<   SoaErrorCodeUtil::getString(errorCode) << std::endl;
        }
    }
    ~ConnectionListenerBase() override = default;
};

/**
 * Listener for Consumer initilization status
 */
class InitializedConsumerListenerBase : public SoaConsumer::SoaInitializedConsumerListener {
public:
    InitializedConsumerListenerBase():
     SoaConsumer::SoaInitializedConsumerListener() {}

    void onInitialized( SoaErrorCode errorCode, const SoaConsumer * consumer) override {       
        if (errorCode ==  SoaErrorCode::NO_ERROR) {
            std::cout << "onInitialized" << std::endl;   
            {
                std::lock_guard<std::mutex> lock(mut_init);                  
                isInitialized = true;
            }
            cv_init.notify_one(); 
        } else {
            std::cout << "Initialization Failed: " <<   SoaErrorCodeUtil::getString(errorCode) << std::endl;
        }
    }
    void onDeinitialized( SoaErrorCode errorCode, const SoaConsumer * consumer) override{
        if (errorCode == SoaErrorCode::NO_ERROR) {
            std::cout << "onDeinitialized" << std::endl;
            std::lock_guard<std::mutex> lock(mut_init);
            isInitialized = false;

        } else {
            std::cout << "Deinitialization Failed: " <<  SoaErrorCodeUtil::getString(errorCode) << std::endl;
        }
    }
    ~InitializedConsumerListenerBase() override = default;
};

/**
 * Base test class is wrapped to securely deregister its listener
 * parents from the SoaResourceManager in most derived destructor
 * before any resources are destroyed.
 */
typedef  SoaListenerLifecycleHelper<
                                DataListenerBase,
                                SoaDataListener
                                > DataListener;

typedef  SoaListenerLifecycleHelper<
                                SubscribeActionListenerBase,
                                SoaActionResultListener< SoaSubscribeToDataContext>
                                > SubscribeActionListener;

typedef  SoaListenerLifecycleHelper<
                                UnsubscribeActionListenerBase,
                                SoaActionResultListener< SoaUnsubscribeToDataContext>
                                > UnsubscribeActionListener;

typedef  SoaListenerLifecycleHelper<
                                ConnectionLostListenerBase,
                                SoaConnectionLostListener
                                > ConnectionLostListener;

typedef  SoaListenerLifecycleHelper<
                                ReconnectionListenerBase,
                                SoaReconnectionListener
                                > ReconnectionListener;

typedef  SoaListenerLifecycleHelper<
                                ConnectionListenerBase,
                                SoaConnectionListener
                                > ConnectionListener;

typedef  SoaListenerLifecycleHelper<
                                InitializedConsumerListenerBase,
                                SoaConsumer::SoaInitializedConsumerListener
                                > InitializedConsumerListener;

int execute(uid_t uid) {
    
    if (uid !=0 ) {
        SoaTestUtils::changeUser(uid);
    }
    SoaErrorCode status;
    DataListener dataListener;
    SubscribeActionListener subActListener;
    UnsubscribeActionListener unsubActListener;

    SoaConnectionOptionsIpc::SharedPtr m_connectionOptions;

    m_connectionOptions =  SoaConnectionOptionsIpc::createConnectionOptionsIpc();
    ConnectionListener connListener;
    m_connectionOptions->setConnectionListener(connListener);
    ConnectionLostListener connLostListener;
    m_connectionOptions->setConnectionLostListener(connLostListener);
    m_connectionOptions->setReconnectionListener(*new ReconnectionListener());

    SoaMessageManager::SharedPtr msgMan =  SoaMessageManager::createMessageManager(*m_connectionOptions);
    SoaServiceDirectoryManager::SharedPtr svcDirMan =  SoaServiceDirectoryManager::create(msgMan, CONSUMER_SDM_ENDPOINT);
    SoaConsumer::SharedPtr consumer =  SoaConsumer::createSoaConsumer(msgMan, svcDirMan, CONSUMER_ENDPOINT);
    //SoaConsumer::initialize() calls SoaMessageManager::connect() if connection is not established
    msgMan->connectAsync();

    InitializedConsumerListener initListener;
    status = consumer->initializeAsync(initListener);

    if(status !=  SoaErrorCode::NO_ERROR){
        std::cout<<"async_subscribe_test: consumer initialization failed"<<std::endl;
        return 1;
    }
 
    {
        std::unique_lock<std::mutex> lock(mut_init);
        if (cv_init.wait_for(lock, INIT_TIMEOUT, [&]{ return isInitialized; })) {    
            std::cout << "Initialized Successfully" << std::endl;       
        } else {
            std::cout << "Initialize failed" << std::endl;
            return 1;
        }   
    }

    consumer->subscribeToDataAsync(DATA_ENDPOINT, dataListener, subActListener);
    {
        std::unique_lock<std::mutex> lock(mut_sub);
        if (cv_sub.wait_for(lock, ACTION_TIMEOUT, [&]{ return  isCallbackCalled; })) {
            std::cout<<"async_subscribe_test: subscribe action done"<<std::endl;
            isCallbackCalled = false; 
            if (actionStatus !=  SoaErrorCode::NO_ERROR){
                std::cout<<"async_subscribe_test: subscribe to data endpoint failed"<<std::endl;
                return 1;
            }
        }
        else {      
            std::cout<<"async_subscribe_test: subscribe action timeout"<<std::endl;
            return 1;
        }
        
    }
    std::cout<<"async_subscribe_test: waiting for data"<<std::endl;
    while (1) {
        std::unique_lock<std::mutex> lock(mut_data);
        if (cv_data.wait_for(lock, MSG_TIMEOUT, [&]{ return isDataReceived; })) {
            std::cout << ("async_subscribe_test: data received - " + dataMsg->getRawPayload() + "\n");
            isDataReceived = false;
        }
        else {
            std::cout<<"async_subscribe_test: timeout"<<std::endl;
            break;
        }  
    }
    
    consumer->unsubscribeToDataAsync(DATA_ENDPOINT, dataListener, unsubActListener);
    {
        std::unique_lock<std::mutex> lock(mut_unsub);
        if (cv_unsub.wait_for(lock, ACTION_TIMEOUT, [&]{ return  isCallbackCalled; })) {
            std::cout<<"async_subscribe_test: unsubscribe action done"<<std::endl;
            if (actionStatus !=  SoaErrorCode::NO_ERROR){
                std::cout<<"async_subscribe_test: unsubscribe to data endpoint failed"<<std::endl;
                return 1;
            }
           
        } else {
            std::cout<<"async_subscribe_test: unsubscribe action timeout"<<std::endl;
            return 1;
        }           
    }
    
    status = msgMan->disconnect();

    if(status !=  SoaErrorCode::NO_ERROR){
        std::cout<<"sync_subscribe_test: disconnect failed"<<std::endl;
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
 * Consumer subscribes to data service endpoint "SERVICES/DATA/UNIQUE_DATA_ENDPOINT"
 * 1. Create a soa client with uid as parameter
 * 2. Connect to Soa gateway using non-blocking method
 * 3. Call initialize asynchronized
 * 4. Subscribe to data service
 * 5. Wait for the arrival of the data for a timeout. Disconnect.
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
