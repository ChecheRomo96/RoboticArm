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
#ifndef MOTOR_TYPES_H
#define MOTOR_TYPES_H

    #include <stdint.h>

    typedef enum
    {
        MOTOR_DIRECTION_CW = 0,
        MOTOR_DIRECTION_CCW = 1
    } MotorDirection;

    typedef enum
    {
        MOTOR_STOPPED = 0,
        MOTOR_RUNNING = 1
    } MotorState;

    typedef struct
    {
        uint16_t pwm;
        MotorDirection direction;
        int32_t position;
    } MotorStatus;

#endif
/* [] END OF FILE */
