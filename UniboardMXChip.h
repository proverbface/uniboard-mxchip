#ifndef UNIBOARD_MXCHIP
#define UNIBOARD_MXCHIP

#include <AZ3166WiFi.h>
#include "MQTTClient.h"
#include "MQTTNetwork.h"

class UniboardMXChip {
private:
    char* token = "";
    const char* host = "uniboard.io";
    int port = 1883;
    MQTTNetwork mqttNetwork;
    MQTT::Client<MQTTNetwork, Countdown> *client;
    WiFiClient httpClient;

public:
    UniboardMXChip(){};

    UniboardMXChip(char* token) : token(token) {};

    int connectMQTT() {
        client = new MQTT::Client<MQTTNetwork, Countdown>(mqttNetwork);
        int rc = mqttNetwork.connect(host, port);
        
        MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
        data.MQTTVersion = 3;
        if (token[0] != '\0') {
            data.clientID.cstring = token;
        } else {
            data.clientID.cstring = "DefaultClientID";
        }        

        rc = client -> connect(data);
        return rc;
    };

    void mqtt(char* topic, char* data) {
        MQTT::Message message;

        // QoS 0
        message.qos = MQTT::QOS0;
        message.retained = false;
        message.dup = false;
        message.payload = (void*)data;
        message.payloadlen = strlen(data);
        client -> publish(topic, message);
    };

    void disconnectMQTT() {
        client -> disconnect();
        mqttNetwork.disconnect();
    }

    void http(char* deviceId, char* data) {
        if (!httpClient.connected()) {
            httpClient.connect(host, 80);
        }

        httpClient.print("POST /data_api/device/");
        httpClient.print(deviceId);
        httpClient.println(" HTTP/1.1");
        httpClient.println("Host: uniboard.io");
        if (token[0] != '\0') {
            httpClient.print("X-Uniboard-Token: ");
            httpClient.println(token);
        }
        httpClient.println("Content-Type: application/json");
        httpClient.print("Content-Length: ");
        httpClient.println(strlen(data));
        httpClient.println("Connection: keep-alive\r\n");
        httpClient.println(data);
    }

    void disconnectHTTP() {
        httpClient.stop();
    } 

    ~UniboardMXChip() {
        delete client;
    }
};

#endif