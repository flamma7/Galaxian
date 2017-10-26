/*
 * buzzer_test.c
 *
 *  Created on: Oct 26, 2017
 *      Author: luke
 */

#include "Headers/buzzer_test.h"
#include "../Drivers/Headers/buzzer.h"
#include "../Drivers/Headers/uart.h"

void Test_Buzzer()
{
    transmit_str("Testing Buzzer");
    config_buzzer(BUZZER_BEEP);
    buzz();
}
