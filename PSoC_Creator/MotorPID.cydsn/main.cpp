/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

extern "C" {
    #include "project.h"
}

#include "Motors.hpp"
#include "Servos.hpp"

#include <Foundation/Math/Arithmetic.h>
#include <Foundation/Math/Ratio.h>

#include <stdio.h>

using namespace Foundation;

int main(void)
{
    CyGlobalIntEnable;

    UART_Start();
    Hardware::Servos_Start();
    Hardware::Motors_Start();

    
    for(;;) {
        
    }
}

/* [] END OF FILE */