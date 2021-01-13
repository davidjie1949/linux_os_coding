#include "paho_test_utils.h"

int publish(const string &PAYLOAD, const string &CLIENTID, const string &TOPIC, const int &QOS, const unsigned int &TIMEOUT){

        const string ADDRESS  = "tcp://mqtt.eclipse.org:1883";
        //const string ADDRESS	= "tcp://192.168.1.21:1883";

        MQTTClient client;
        MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
        MQTTClient_message pubmsg = MQTTClient_message_initializer;
        MQTTClient_deliveryToken token;
        int rc = 0;

        if ((rc = MQTTClient_create(&client, ADDRESS.c_str(), CLIENTID.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS){
            cout << "Failed to create client, return code" + to_string(rc) << endl;
            exit(EXIT_FAILURE);
        }

        conn_opts.keepAliveInterval = 20;
        conn_opts.cleansession = 1;
    //    conn_opts.username = "jie";
    //    conn_opts.password = "jie";

        if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS){
            cout << "Failed to connect, return code" + to_string(rc) << endl;
            exit(EXIT_FAILURE);
        }

        pubmsg.payload = (void*)PAYLOAD.c_str();
        pubmsg.payloadlen = PAYLOAD.length();
        pubmsg.qos = QOS;
        pubmsg.retained = 0;

        if ((rc = MQTTClient_publishMessage(client, TOPIC.c_str(), &pubmsg, &token)) != MQTTCLIENT_SUCCESS){
             cout << "Failed to publish message, return code " + to_string(rc) << endl;
             exit(EXIT_FAILURE);
        }

        cout << "Waiting for up to " + to_string((int)(TIMEOUT/1000)) + " seconds for publication of " + PAYLOAD << endl;
        cout << "on topic " + TOPIC << endl;
        cout << "for client with ClientID: " + CLIENTID << endl;

        rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        cout << "Message with delivery token " + to_string(token) + " delivered" << endl;

        if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
            cout << "Failed to disconnect, return " + to_string(rc) << endl;

        MQTTClient_destroy(&client);

        return 0;
}
