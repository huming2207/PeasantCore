//
// Created by Ming Hu on 15/9/17.
//

#ifndef PEASANTCORE_NETWORK_H
#define PEASANTCORE_NETWORK_H

#include <Arduino.h>
#include <Preferences.h>
#include "WiFi.h"

#define NETWORK_PREF_NAME "net_pref"
#define WIFI_AP_SSID_PERFIX "Peasant-"
#define WIFI_AP_PASSWORD "1234567890"

class Network
{
    public:
        bool init();
        bool saveCredential();
        bool loadCredential();
        
    private:
        Preferences networkPreferences;
        bool firstBoot;
        void wifiEventCallback(WiFiEvent_t event);
};

#endif //PEASANTCORE_NETWORK_H
