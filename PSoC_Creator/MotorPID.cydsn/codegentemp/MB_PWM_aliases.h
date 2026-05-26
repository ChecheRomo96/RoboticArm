/*******************************************************************************
* File Name: MB_PWM.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MB_PWM_ALIASES_H) /* Pins MB_PWM_ALIASES_H */
#define CY_PINS_MB_PWM_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define MB_PWM_0			(MB_PWM__0__PC)
#define MB_PWM_0_INTR	((uint16)((uint16)0x0001u << MB_PWM__0__SHIFT))

#define MB_PWM_INTR_ALL	 ((uint16)(MB_PWM_0_INTR))

#endif /* End Pins MB_PWM_ALIASES_H */


/* [] END OF FILE */
