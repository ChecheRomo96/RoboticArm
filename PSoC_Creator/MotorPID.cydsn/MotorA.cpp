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
    
            void Start(){
                MotorA_Start();
            }
            
            uint16_t GetPosition(){
                return MotorA_GetPosition();
            }
            
            void SetPWM(uint16_t value){
                MotorA_SetPWM(value);
            }

            uint16_t ReadPWM(){
                return MotorA_ReadPWM();
            }
            void SetDirection(bool dir){
                MotorA_SetDirection(dir);
            }
        }
    }
    
    
#endif//MOTOR_A_HPP
/* [] END OF FILE */
