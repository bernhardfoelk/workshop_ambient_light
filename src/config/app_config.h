/**
 * 
 * @brief Configuration file for all parameters
 * 
 * @file app_config.h
 * @author Bernhard Fölk
 * @date 19.10.2025
 * 
 */

 #pragma once

 #include <Arduino.h>

 #define DEBUGGING true

 #if DEBUGGING == true
    #define debug(x) Serial.print(x)
    #define debugln(x) Serial.println(x)
 #else
    #define debug(x) 
    #define debugln(x)
 #endif

// Constants
#define POWER_BUTTON 2
#define BUTTON_RED 0
#define BUTTON_GREEN 4
#define BUTTON_BLUE 5