/*******************************************************************************
* File Name: MotorA_QuadDec.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_QUADRATURE_DECODER_MotorA_QuadDec_H)
#define CY_QUADRATURE_DECODER_MotorA_QuadDec_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define MotorA_QuadDec_COUNTER_SIZE               (16u)
#define MotorA_QuadDec_COUNTER_SIZE_8_BIT         (8u)
#define MotorA_QuadDec_COUNTER_SIZE_16_BIT        (16u)
#define MotorA_QuadDec_COUNTER_SIZE_32_BIT        (32u)

#if (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT)
    #include "MotorA_QuadDec_Cnt8.h"
#else 
    /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_16_BIT) || 
    *  (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT) 
    */
    #include "MotorA_QuadDec_Cnt16.h"
#endif /* MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT */

extern uint8 MotorA_QuadDec_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define MotorA_QuadDec_COUNTER_RESOLUTION         (4u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} MotorA_QuadDec_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  MotorA_QuadDec_Init(void) ;
void  MotorA_QuadDec_Start(void) ;
void  MotorA_QuadDec_Stop(void) ;
void  MotorA_QuadDec_Enable(void) ;
uint8 MotorA_QuadDec_GetEvents(void) ;
void  MotorA_QuadDec_SetInterruptMask(uint8 mask) ;
uint8 MotorA_QuadDec_GetInterruptMask(void) ;
int16 MotorA_QuadDec_GetCounter(void) ;
void  MotorA_QuadDec_SetCounter(int16 value)
;
void  MotorA_QuadDec_Sleep(void) ;
void  MotorA_QuadDec_Wakeup(void) ;
void  MotorA_QuadDec_SaveConfig(void) ;
void  MotorA_QuadDec_RestoreConfig(void) ;

#if (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(MotorA_QuadDec_ISR);
#endif /* MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT)
    #define MotorA_QuadDec_ISR_NUMBER             ((uint8) MotorA_QuadDec_isr__INTC_NUMBER)
    #define MotorA_QuadDec_ISR_PRIORITY           ((uint8) MotorA_QuadDec_isr__INTC_PRIOR_NUM)
#endif /* MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define MotorA_QuadDec_GLITCH_FILTERING           (1u)
#define MotorA_QuadDec_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT)
    #define MotorA_QuadDec_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_16_BIT) ||
    *  (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT)
    */
    #define MotorA_QuadDec_COUNTER_INIT_VALUE    (0x8000u)
    #define MotorA_QuadDec_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define MotorA_QuadDec_STATUS_REG                 (* (reg8 *) MotorA_QuadDec_bQuadDec_Stsreg__STATUS_REG)
#define MotorA_QuadDec_STATUS_PTR                 (  (reg8 *) MotorA_QuadDec_bQuadDec_Stsreg__STATUS_REG)
#define MotorA_QuadDec_STATUS_MASK                (* (reg8 *) MotorA_QuadDec_bQuadDec_Stsreg__MASK_REG)
#define MotorA_QuadDec_STATUS_MASK_PTR            (  (reg8 *) MotorA_QuadDec_bQuadDec_Stsreg__MASK_REG)
#define MotorA_QuadDec_SR_AUX_CONTROL             (* (reg8 *) MotorA_QuadDec_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define MotorA_QuadDec_SR_AUX_CONTROL_PTR         (  (reg8 *) MotorA_QuadDec_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define MotorA_QuadDec_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define MotorA_QuadDec_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define MotorA_QuadDec_COUNTER_RESET_SHIFT        (0x02u)
#define MotorA_QuadDec_INVALID_IN_SHIFT           (0x03u)
#define MotorA_QuadDec_COUNTER_OVERFLOW           ((uint8) (0x01u << MotorA_QuadDec_COUNTER_OVERFLOW_SHIFT))
#define MotorA_QuadDec_COUNTER_UNDERFLOW          ((uint8) (0x01u << MotorA_QuadDec_COUNTER_UNDERFLOW_SHIFT))
#define MotorA_QuadDec_COUNTER_RESET              ((uint8) (0x01u << MotorA_QuadDec_COUNTER_RESET_SHIFT))
#define MotorA_QuadDec_INVALID_IN                 ((uint8) (0x01u << MotorA_QuadDec_INVALID_IN_SHIFT))

#define MotorA_QuadDec_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define MotorA_QuadDec_INTERRUPTS_ENABLE          ((uint8)(0x01u << MotorA_QuadDec_INTERRUPTS_ENABLE_SHIFT))
#define MotorA_QuadDec_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define MotorA_QuadDec_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_MotorA_QuadDec_H */


/* [] END OF FILE */
