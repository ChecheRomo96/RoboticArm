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
#ifndef HARDWARE_HPP
#define HARDWARE_HPP

    #include "Motors.hpp"
    #include "Servos.hpp"
    
    namespace Hardware{
    
        void Start(){
            Hardware::Servos_Start();
            Hardware::Motors_Start();
        }
    }

#endif//HARDWARE_HPP
/* [] END OF FILE */
