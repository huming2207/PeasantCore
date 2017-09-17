//
// Created by Ming Hu on 15/9/17.
//

#include "Network.h"

bool Network::init()
{
    // Load preference with network namespace
    networkPreferences.begin(NETWORK_PREF_NAME, false);

    // Detect if it's the first boot, default is true if this value is not found
    firstBoot = networkPreferences.getBool("first_boot", true);

    if(firstBoot)
    {
        // Set fist boot flag to false
        networkPreferences.putBool("first_boot", false);

        // Reset WiFi before further actions? (According to the sample code... But why???)
        WiFi.disconnect(true);
        WiFi.mode(WIFI_AP);

        // Get the SSID string with chip ID
        String wifiSsid = WIFI_AP_SSID_PERFIX + String((uint16_t)(ESP.getEfuseMac()>>32), HEX);
        
        WiFi.softAP(wifiSsid.c_str(), WIFI_AP_PASSWORD);
    }

}

bool Network::loadCredential()
{

}

bool Network::saveCredential()
{

}

void Network::wifiEventCallback(WiFiEvent_t event)
{
    switch(event)
    {
        case SYSTEM_EVENT_AP_START:
        {
            break;
        }

        case SYSTEM_EVENT_STA_START:
        {
            break;
        }

        case SYSTEM_EVENT_STA_CONNECTED:
        {
            break;
        }

        case SYSTEM_EVENT_STA_DISCONNECTED:
        {
            break;
        }

        case SYSTEM_EVENT_STA_GOT_IP:
        {
            break;
        }
    }
}
