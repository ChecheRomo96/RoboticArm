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
    #include "project.h"

    void ServoDriver_Start(){
        Servo_PWM_Start();
        ServoAB_Start();
        ServoCD_Start();
    }
    
    void ServoA_SetPositionTicks(uint16_t x){
        if(x > ServoAB_ReadPeriod()){
            return;
        }
        
        ServoAB_WriteCompare1(x);
    }
    
    void ServoA_SetPositionNorm(float x){
        if((x > 1.0) || (x < 0.0f)){
            return;
        }
        
        uint16_t y = ServoAB_ReadPeriod() * (1.0 - x);
        
        ServoAB_WriteCompare1(y);
    }
    
    uint16_t ServoA_GetPositionTicks(){
        // Implementation for getting position in ticks of ServoA
        return ServoAB_ReadCompare1();
    }
    
    float ServoA_GetPositionNorm(){
        // Implementation for getting normalized position of ServoA
        return 1.0 - ((float)ServoAB_ReadCompare1() / (float)ServoAB_ReadPeriod());
    }
    
    
    void ServoB_SetPositionTicks(uint16_t x){
        if(x > ServoAB_ReadPeriod()){
            return;
        }
        
        ServoAB_WriteCompare2(x);
    }
    
    void ServoB_SetPositionNorm(float x){
        if((x > 1.0) || (x < 0.0f)){
            return;
        }
        
        uint16_t y = ServoAB_ReadPeriod() * (1.0 - x);
        
        ServoAB_WriteCompare2(y);
    }
    
    uint16_t ServoB_GetPositionTicks(){
        // Implementation for getting position in ticks of ServoB
        return ServoAB_ReadCompare2();
    }
    
    float ServoB_GetPositionNorm(){
        // Implementation for getting normalized position of ServoB
        return 1.0 - ((float)ServoAB_ReadCompare2() / (float)ServoAB_ReadPeriod());
    }

    
    void ServoC_SetPositionTicks(uint16_t x){
        if(x > ServoCD_ReadPeriod()){
            return;
        }
        
        ServoCD_WriteCompare1(x);
    }
    
    void ServoC_SetPositionNorm(float x){
        if((x > 1.0) || (x < 0.0f)){
            return;
        }
        
        uint16_t y = ServoCD_ReadPeriod() * (1.0 - x);
        
        ServoCD_WriteCompare1(y);
    }
    
    uint16_t ServoC_GetPositionTicks(){
        // Implementation for getting position in ticks of ServoC
        return ServoCD_ReadCompare1();
    }
    
    float ServoC_GetPositionNorm(){
        // Implementation for getting normalized position of ServoC
        return 1.0 - ((float)ServoCD_ReadCompare1() / (float)ServoCD_ReadPeriod());
    }

    
    
    void ServoD_SetPositionTicks(uint16_t x){
        if(x > ServoCD_ReadPeriod()){
            return;
        }
        
        ServoCD_WriteCompare2(x);
    }
    
    void ServoD_SetPositionNorm(float x){
        if((x > 1.0) || (x < 0.0f)){
            return;
        }
        
        uint16_t y = ServoCD_ReadPeriod() * (1.0 - x);
        
        ServoCD_WriteCompare2(y);
    }
    
    uint16_t ServoD_GetPositionTicks(){
        // Implementation for getting position in ticks of ServoD
        return ServoCD_ReadCompare2();
    }
    
    float ServoD_GetPositionNorm(){
        // Implementation for getting normalized position of ServoD
        return 1.0 - ((float)ServoCD_ReadCompare2() / (float)ServoCD_ReadPeriod());
    }

/* [] END OF FILE */
