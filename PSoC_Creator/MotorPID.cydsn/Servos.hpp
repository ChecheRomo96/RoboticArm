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
            void SetPosition(float pos);
            void SetPosition(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        namespace ServoB {
            void SetPosition(float pos);
            void SetPosition(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        namespace ServoC {
            void SetPosition(float pos);
            void SetPosition(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        namespace ServoD {
            void SetPosition(float pos);
            void SetPosition(uint16_t pos);
            uint16_t GetPositionTicks();
            float GetPositionNorm();
        }

        void Servos_Start();
    }
    
#endif//SERVOS_H
/* [] END OF FILE */
