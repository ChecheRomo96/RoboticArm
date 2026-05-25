/*******************************************************************************
* File Name: MotorA_ISR.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_MotorA_ISR_H)
#define CY_ISR_MotorA_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MotorA_ISR_Start(void);
void MotorA_ISR_StartEx(cyisraddress address);
void MotorA_ISR_Stop(void);

CY_ISR_PROTO(MotorA_ISR_Interrupt);

void MotorA_ISR_SetVector(cyisraddress address);
cyisraddress MotorA_ISR_GetVector(void);

void MotorA_ISR_SetPriority(uint8 priority);
uint8 MotorA_ISR_GetPriority(void);

void MotorA_ISR_Enable(void);
uint8 MotorA_ISR_GetState(void);
void MotorA_ISR_Disable(void);

void MotorA_ISR_SetPending(void);
void MotorA_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MotorA_ISR ISR. */
#define MotorA_ISR_INTC_VECTOR            ((reg32 *) MotorA_ISR__INTC_VECT)

/* Address of the MotorA_ISR ISR priority. */
#define MotorA_ISR_INTC_PRIOR             ((reg8 *) MotorA_ISR__INTC_PRIOR_REG)

/* Priority of the MotorA_ISR interrupt. */
#define MotorA_ISR_INTC_PRIOR_NUMBER      MotorA_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MotorA_ISR interrupt. */
#define MotorA_ISR_INTC_SET_EN            ((reg32 *) MotorA_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MotorA_ISR interrupt. */
#define MotorA_ISR_INTC_CLR_EN            ((reg32 *) MotorA_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MotorA_ISR interrupt state to pending. */
#define MotorA_ISR_INTC_SET_PD            ((reg32 *) MotorA_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MotorA_ISR interrupt. */
#define MotorA_ISR_INTC_CLR_PD            ((reg32 *) MotorA_ISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_MotorA_ISR_H */


/* [] END OF FILE */
