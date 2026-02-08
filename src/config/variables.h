/**
 * 
 * @brief File that stores all variable definitions
 * 
 * @file app_config.h
 * @author Bernhard Fölk
 * @date 25.10.2025
 * 
 */

#include <Ton.h>
#include <EdgePosNeg.h>

// 
// local variables
bool lxPower = false;

struct sLedState
{
    int iValue;
};
sLedState lsLedRed;
sLedState lsLedGreen;
sLedState lsLedBlue;

int liLedValue = 0;
int liStep = 0;
int liStepOld = 0;

bool lxTemp = false;

// Timer
Ton TonStep;

// Edge detection for buttons
EdgePosNeg Edge_PowerButton;
EdgePosNeg Edge_ButtonRed;
EdgePosNeg Edge_ButtonGreen;
EdgePosNeg Edge_ButtonBlue;