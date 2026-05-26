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
#ifndef SERVOS_HW_H
#define SERVOS_HW_H
    #include "project.h"

    void ServoDriver_Start();
    
    void ServoA_SetPositionTicks(uint16_t x);
    void ServoA_SetPositionNorm(float x);
    uint16_t ServoA_GetPositionTicks();
    float ServoA_GetPositionNorm();
    
    void ServoB_SetPositionTicks(uint16_t x);
    void ServoB_SetPositionNorm(float x);
    uint16_t ServoB_GetPositionTicks();
    float ServoB_GetPositionNorm();
    
    void ServoC_SetPositionTicks(uint16_t x);
    void ServoC_SetPositionNorm(float x);
    uint16_t ServoC_GetPositionTicks();
    float ServoC_GetPositionNorm();
    
    void ServoD_SetPositionTicks(uint16_t x);
    void ServoD_SetPositionNorm(float x);
    uint16_t ServoD_GetPositionTicks();
    float ServoD_GetPositionNorm();
    
#endif
/* [] END OF FILE */
