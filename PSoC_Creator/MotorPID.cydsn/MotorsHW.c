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
    #include "MotorTypes.h"
    #include "MotorsHW.h"
    
    // Motor A

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

    MotorStatus MotorA_GetStatus(){
        MotorStatus state;
        state.direction = MotorA_GetPosition();
        state.pwm = MotorA_ReadPWM();
        state.position = MotorA_GetPosition();
        return state;
    }

    // Motor B

    CY_ISR(MotorB_ISR){
        
        uint8_t mask = MotorB_QuadDec_GetEvents();
        
        if(mask & MotorB_QuadDec_COUNTER_OVERFLOW){
            
        }
        else if(mask & MotorB_QuadDec_COUNTER_UNDERFLOW){
            
        }
        
        if(mask & MotorB_QuadDec_INVALID_IN){
            
        }
    }

    void MotorB_Start(){
        
        MotorB_PWM_Start();
        
        MotorB_QuadDec_Start();
        MotorB_QuadDec_SetInterruptMask(
            MotorB_QuadDec_COUNTER_OVERFLOW|
            MotorB_QuadDec_COUNTER_UNDERFLOW|
            MotorB_QuadDec_INVALID_IN
        );
        
        MotorB_ISR_StartEx(MotorB_ISR);
        
    }
    
    uint16_t MotorB_GetPosition(){
        return MotorB_QuadDec_GetCounter();
    }
    
    void MotorB_SetPWM(uint16_t value){
        MotorB_PWM_WriteCompare(value);
    }
    
    uint16_t MotorB_ReadPWM(){
        return MotorB_PWM_ReadCompare();
    }
    
    void MotorB_SetDirection(bool dir){
        if(dir){
            MotorB_Dir_Write(1); // CW
        } else {
            MotorB_Dir_Write(0); // CCWW
        }
    }

    MotorStatus MotorB_GetStatus(){
        MotorStatus state;
        state.direction = MotorB_GetPosition();
        state.pwm = MotorB_ReadPWM();
        state.position = MotorB_GetPosition();
        return state;
    }
    
/* [] END OF FILE */
