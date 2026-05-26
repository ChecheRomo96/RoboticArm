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
#ifndef MOTORS_H
#define MOTORS_H
    
    #include "MotorTypes.h"
    
    namespace Hardware{
        void Motors_Start();
    
        namespace MotorA{
            void Start();
            uint16_t GetPosition();
            void SetPWM(uint16_t value);
            uint16_t ReadPWM();
            void SetDirection(bool dir);
            MotorStatus Status();
        }
        
        namespace MotorB{
            void Start();
            uint16_t GetPosition();
            void SetPWM(uint16_t value);
            uint16_t ReadPWM();
            void SetDirection(bool dir);
            MotorStatus Status();
        }
    }
    
#endif//MOTORS_H
/* [] END OF FILE */
