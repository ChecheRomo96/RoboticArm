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
#ifndef MOTOR_A_HPP
#define MOTOR_A_HPP
    
    extern "C"{
        #include "project.h"
        #include "MotorA_HW.h"
    }
    
    namespace Hardware{
        namespace MotorA{
            void Start();
            uint16_t GetPosition();
            void SetPWM(uint16_t value);
            uint16_t ReadPWM();
            void SetDirection(bool dir);
        }
    }
    
    
#endif//MOTOR_A_HPP
/* [] END OF FILE */
