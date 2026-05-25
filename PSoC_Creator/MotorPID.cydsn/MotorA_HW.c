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
    #include "MotorA_HW.h"
    
    CY_ISR(MotorA_ISR){
        
        uint8_t mask = MotorA_QuadDec_GetEvents();
        
        if(mask & MotorA_QuadDec_COUNTER_OVERFLOW){
            
        }
        else if(mask & MotorA_QuadDec_COUNTER_UNDERFLOW){
            
        }
        
        if(mask & MotorA_QuadDec_INVALID_IN){
            
        }
    }
    
    void MotorA_Start(){
        
        MotorA_PWM_Start();
        
        MotorA_QuadDec_Start();
        MotorA_QuadDec_SetInterruptMask(
            MotorA_QuadDec_COUNTER_OVERFLOW|
            MotorA_QuadDec_COUNTER_UNDERFLOW|
            MotorA_QuadDec_INVALID_IN
        );
        
        MotorA_ISR_StartEx(MotorA_ISR);
        
    }
    
    uint16_t MotorA_GetPosition(){
        return MotorA_QuadDec_GetCounter();
    }
    
    void MotorA_SetPWM(uint16_t value){
        MotorA_PWM_WriteCompare(value);
    }
    
    uint16_t MotorA_ReadPWM(){
        return MotorA_PWM_ReadCompare();
    }
    
    void MotorA_SetDirection(bool dir){
        if(dir){
            MotorA_Dir_Write(1); // CW
        } else {
            MotorA_Dir_Write(0); // CCWW
        }
    }
    
    
/* [] END OF FILE */
