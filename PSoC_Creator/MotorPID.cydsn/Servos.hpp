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
#ifndef SERVOS_H
#define SERVOS_H
    
    #include <stdint.h>

    namespace Hardware {

        namespace ServoA {
            void SetPositionNorm(float pos);
            void SetPositionTicks(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        namespace ServoB {
            void SetPositionNorm(float pos);
            void SetPositionTicks(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        namespace ServoC {
            void SetPositionNorm(float pos);
            void SetPositionTicks(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        namespace ServoD {
            void SetPositionNorm(float pos);
            void SetPositionTicks(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        void Servos_Start();
    }
    
#endif//SERVOS_H
/* [] END OF FILE */
