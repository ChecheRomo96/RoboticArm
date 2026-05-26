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
  
    extern "C"{
        #include "project.h"
        #include "MotorsHW.h"
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
            
            MotorStatus Status(){
                return MotorA_GetStatus();
            }
        }
        
        namespace MotorB{
    
            void Start(){
                MotorB_Start();
            }
            
            uint16_t GetPosition(){
                return MotorB_GetPosition();
            }
            
            void SetPWM(uint16_t value){
                MotorB_SetPWM(value);
            }

            uint16_t ReadPWM(){
                return MotorB_ReadPWM();
            }
            void SetDirection(bool dir){
                MotorB_SetDirection(dir);
            }
            
            MotorStatus Status(){
                return MotorB_GetStatus();
            }
        }
        
        void Motors_Start(){
            MotorA::Start();
            MotorB::Start();
        }
    }
    
/* [] END OF FILE */
