//
// Created by Ming Hu on 15/9/17.
//


#include "main.h"

void setup()
{
    Preferences preferences;
    Network network;

    // Load system namespace
    preferences.begin(PREF_SYSTEM_NAMESPACE);

    // Detect if first boot
    bool firstBoot = preferences.getBool(PREF_FIRST_BOOT_KEY, true);

    //
    if(firstBoot)
    {
        // Load and set the initial wifi settings
        network.init(true);
        preferences.putBool(PREF_FIRST_BOOT_KEY, false);
    }
    else
    {
        // Load network component;
        network.init(false);
    }
}

void loop()
{

}