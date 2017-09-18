//
// Created by Ming Hu on 15/9/17.
//

#include "Network.h"

bool Network::init(bool forceReset)
{
    // Load preference with network namespace
    networkPreferences.begin(PREF_NETWORK_NAMESPACE, false);

    if(forceReset)
    {
        Serial.println("[SYSTEM] First boot detected!");
        Serial.println("[NETWORK] Connecting to WiFi in AP MODE...");

        // Set fist boot flag to false
        networkPreferences.clear();

        // Reset WiFi before further actions? (According to the sample code... But why???)
        WiFi.disconnect(true);
        WiFi.mode(WIFI_AP);

        // Get the SSID string with chip ID
        String wifiSsid = String(WIFI_AP_SSID_PERFIX) + String((uint16_t)(ESP.getEfuseMac()>>32), HEX);
        WiFi.softAP(wifiSsid.c_str(), WIFI_AP_PASSWORD);
    }
    else
    {
        Serial.print("[NETWORK] Connecting to WiFi in CLIENT MODE...");

        // Reset WiFi and set to client mode
        WiFi.disconnect(true);
        WiFi.mode(WIFI_STA);

        // Get SSID and password config, if empty, do force reset
        String wifiSsid = networkPreferences.getString(PREF_WIFI_SSID, PREF_WIFI_DEFAULT_SSID);
        String wifiPasswd = networkPreferences.getString(PREF_WIFI_PASSWD, PREF_WIFI_DEFAULT_PASSWD);

        if(wifiSsid.length() < 1)
        {
            // Do force reset as SSID value is corrupted.
            init(true);
        }
        else if(wifiPasswd.length() < 1)
        {
            WiFi.begin(wifiSsid.c_str());
        }
        else
        {
            WiFi.begin(wifiSsid.c_str(), wifiPasswd.c_str());
        }

        WiFi.onEvent(wifiEventCallback);
    }

}

void Network::setTime()
{
    xTaskCreate(_setTimeTask, "SetTime", 10000, (void *)timeZone.c_str(), 1, NULL);
}

void Network::wifiEventCallback(WiFiEvent_t event)
{
    switch(event)
    {
        case SYSTEM_EVENT_AP_START:
        {
            Serial.println("[NETWORK] AP mode started!");
            break;
        }

        case SYSTEM_EVENT_STA_START:
        {
            Serial.println("[NETWORK] Client mode started!");
            break;
        }

        case SYSTEM_EVENT_STA_CONNECTED:
        {
            Serial.println("[NETWORK] Connected to AP!");
            break;
        }

        case SYSTEM_EVENT_STA_DISCONNECTED:
        {
            Serial.println("[NETWORK] Deconnected from AP!");
            break;
        }

        case SYSTEM_EVENT_STA_GOT_IP:
        {
            Serial.print("[NETWORK] IP Address: ");
            Serial.println(WiFi.localIP().toString());
            break;
        }

        case SYSTEM_EVENT_WIFI_READY:
        {
            break;
        }

        case SYSTEM_EVENT_SCAN_DONE:
        {
            break;
        }

        case SYSTEM_EVENT_STA_STOP:
        {
            break;
        }

        case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
        {
            break;
        }

        case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
        {
            break;
        }

        case SYSTEM_EVENT_STA_WPS_ER_FAILED:
        {
            break;
        }

        case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
        {
            break;
        }

        case SYSTEM_EVENT_STA_WPS_ER_PIN:
        {
            break;
        }

        case SYSTEM_EVENT_AP_STOP:
        {
            break;
        }

        case SYSTEM_EVENT_AP_STACONNECTED:
        {
            break;
        }

        case SYSTEM_EVENT_AP_STADISCONNECTED:
        {
            break;
        }

        case SYSTEM_EVENT_AP_PROBEREQRECVED:
        {
            break;
        }

        case SYSTEM_EVENT_AP_STA_GOT_IP6:
        {
            break;
        }
    }
}

void _setTimeTask(void * parameter)
{
    configTzTime((char *)parameter, TIME_NTP_SERVER_1, TIME_NTP_SERVER_2, TIME_NTP_SERVER_3);

    struct tm timeinfo;

    if(!getLocalTime(&timeinfo))
    {
        Serial.println("[NETWORK] Failed to obtain time!");
        return;
    }

    Serial.print("[NETWORK] Got time: ");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    // Remove this task when finishes (not loop it again)
    vTaskDelete(nullptr);
}

