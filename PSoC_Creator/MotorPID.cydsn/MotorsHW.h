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
    #include "MotorTypes.h"
    #include <stdbool.h>
    
    // Motor A
    
    void MotorA_Start();
    uint16_t MotorA_GetPosition(void);
    void MotorA_SetPWM(uint16_t value);
    uint16_t MotorA_ReadPWM(void);
    void MotorA_SetDirection(bool dir);
    MotorStatus MotorA_GetStatus();
    
    // Motor B
    
    void MotorB_Start();
    uint16_t MotorB_GetPosition(void);
    void MotorB_SetPWM(uint16_t value);
    uint16_t MotorB_ReadPWM(void);
    void MotorB_SetDirection(bool dir);
    MotorStatus MotorB_GetStatus();
    
#endif//MOTOR_A_H
/* [] END OF FILE */
