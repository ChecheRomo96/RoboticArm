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

#include <stdio.h>

#include <Foundation/Math/Arithmetic.h>
#include <Foundation/Math/Ratio.h>

using namespace Foundation;

static void PrintRatio(
    const char* label,
    const Math::Ratio& ratio
) {

    char buffer[128];

    sprintf(
        buffer,
        "%s -> %d * %lu/%lu = %.4lf\r\n",
        label,
        ratio.Sign(),
        (unsigned long)ratio.Num(),
        (unsigned long)ratio.Den(),
        ratio.ToFloat()
    );

    UART_PutString(buffer);
}

int main(void)
{
    CyGlobalIntEnable;

    UART_Start();
    Servo_PWM_Start();
    ServoAB_Start();
    

    UART_PutString("\r\n=== GCD TEST ===\r\n");

    uint32_t gcd1 = Math::GCD(48, 18);
    uint32_t gcd2 = Math::GCD(48000, 44100);

    char buffer[128];

    sprintf(buffer, "GCD(48,18) = %lu\r\n", (unsigned long)gcd1);
    UART_PutString(buffer);

    sprintf(buffer, "GCD(48000,44100) = %lu\r\n", (unsigned long)gcd2);
    UART_PutString(buffer);

    UART_PutString("\r\n=== RATIO TEST ===\r\n");

    Math::Ratio r1(3, 4);
    Math::Ratio r2(-3, 4);
    Math::Ratio r3(3, -4);
    Math::Ratio r4(-3, -4);

    PrintRatio("r1", r1);
    PrintRatio("r2", r2);
    PrintRatio("r3", r3);
    PrintRatio("r4", r4);

    UART_PutString("\r\n=== REDUCTION TEST ===\r\n");

    Math::Ratio r5(48, 18);

    PrintRatio("Original", r5);

    Math::Ratio reduced = r5.Reduced();

    PrintRatio("Reduced", reduced);

    UART_PutString("\r\n=== IN-PLACE REDUCE TEST ===\r\n");

    r5.Reduce();

    PrintRatio("r5", r5);
    
    uint32_t x = 0;
    
    for(;;) {
        
        ServoAB_WriteCompare1(x/100);
        x++;
        x%=2400000;
    }
}

/* [] END OF FILE */