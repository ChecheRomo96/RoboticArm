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
        #include "ServosHW.h"
    }
    
    namespace Hardware{
    
        namespace ServoA{
    
            void SetPosition(float pos){
                ServoA_SetPositionNorm(pos);
            }
            
            void SetPosition(uint16_t pos){
                ServoA_SetPositionTicks(pos);
            }
            
            uint16_t GetPositionTicks(){
                return ServoA_GetPositionTicks();
            }
            
            float GetPositionNorm(){
                return ServoA_GetPositionNorm();
            }
        }
    
        namespace ServoB{
    
            void SetPosition(float pos){
                ServoB_SetPositionNorm(pos);
            }
            
            void SetPosition(uint16_t pos){
                ServoB_SetPositionTicks(pos);
            }
            
            uint16_t GetPositionTicks(){
                return ServoB_GetPositionTicks();
            }
            
            float GetPositionNorm(){
                return ServoB_GetPositionNorm();
            }
        }
    
        namespace ServoC{
    
            void SetPosition(float pos){
                ServoC_SetPositionNorm(pos);
            }
            
            void SetPosition(uint16_t pos){
                ServoC_SetPositionTicks(pos);
            }
            
            uint16_t GetPositionTicks(){
                return ServoC_GetPositionTicks();
            }
            
            float GetPositionNorm(){
                return ServoC_GetPositionNorm();
            }
        }
    
        namespace ServoD{
    
            void SetPosition(float pos){
                ServoD_SetPositionNorm(pos);
            }
            
            void SetPosition(uint16_t pos){
                ServoD_SetPositionTicks(pos);
            }
            
            uint16_t GetPositionTicks(){
                return ServoD_GetPositionTicks();
            }
            
            float GetPositionNorm(){
                return ServoD_GetPositionNorm();
            }
        }
        
        
        void Servos_Start(){
            ServoDriver_Start();
            ServoA::SetPosition(0.5f);
            ServoB::SetPosition(0.5f);
            ServoC::SetPosition(0.5f);
            ServoD::SetPosition(0.5f);
        }
    }
    
/* [] END OF FILE */
