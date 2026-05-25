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
#ifndef MOTOR_A_H
#define MOTOR_A_H
    
    #include "project.h"
    #include <stdbool.h>
    
    void MotorA_Start();
    uint16_t MotorA_GetPosition(void);
    void MotorA_SetPWM(uint16_t value);
    uint16_t MotorA_ReadPWM(void);
    void MotorA_SetDirection(bool dir);
    
#endif//MOTOR_A_H
/* [] END OF FILE */
