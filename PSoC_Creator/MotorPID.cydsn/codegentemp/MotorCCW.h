/*******************************************************************************
* File Name: MotorCCW.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MotorCCW_H) /* Pins MotorCCW_H */
#define CY_PINS_MotorCCW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorCCW_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotorCCW__PORT == 15 && ((MotorCCW__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotorCCW_Write(uint8 value);
void    MotorCCW_SetDriveMode(uint8 mode);
uint8   MotorCCW_ReadDataReg(void);
uint8   MotorCCW_Read(void);
void    MotorCCW_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotorCCW_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotorCCW_SetDriveMode() function.
     *  @{
     */
        #define MotorCCW_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotorCCW_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotorCCW_DM_RES_UP          PIN_DM_RES_UP
        #define MotorCCW_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotorCCW_DM_OD_LO           PIN_DM_OD_LO
        #define MotorCCW_DM_OD_HI           PIN_DM_OD_HI
        #define MotorCCW_DM_STRONG          PIN_DM_STRONG
        #define MotorCCW_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotorCCW_MASK               MotorCCW__MASK
#define MotorCCW_SHIFT              MotorCCW__SHIFT
#define MotorCCW_WIDTH              1u

/* Interrupt constants */
#if defined(MotorCCW__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotorCCW_SetInterruptMode() function.
     *  @{
     */
        #define MotorCCW_INTR_NONE      (uint16)(0x0000u)
        #define MotorCCW_INTR_RISING    (uint16)(0x0001u)
        #define MotorCCW_INTR_FALLING   (uint16)(0x0002u)
        #define MotorCCW_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotorCCW_INTR_MASK      (0x01u) 
#endif /* (MotorCCW__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorCCW_PS                     (* (reg8 *) MotorCCW__PS)
/* Data Register */
#define MotorCCW_DR                     (* (reg8 *) MotorCCW__DR)
/* Port Number */
#define MotorCCW_PRT_NUM                (* (reg8 *) MotorCCW__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorCCW_AG                     (* (reg8 *) MotorCCW__AG)                       
/* Analog MUX bux enable */
#define MotorCCW_AMUX                   (* (reg8 *) MotorCCW__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorCCW_BIE                    (* (reg8 *) MotorCCW__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorCCW_BIT_MASK               (* (reg8 *) MotorCCW__BIT_MASK)
/* Bypass Enable */
#define MotorCCW_BYP                    (* (reg8 *) MotorCCW__BYP)
/* Port wide control signals */                                                   
#define MotorCCW_CTL                    (* (reg8 *) MotorCCW__CTL)
/* Drive Modes */
#define MotorCCW_DM0                    (* (reg8 *) MotorCCW__DM0) 
#define MotorCCW_DM1                    (* (reg8 *) MotorCCW__DM1)
#define MotorCCW_DM2                    (* (reg8 *) MotorCCW__DM2) 
/* Input Buffer Disable Override */
#define MotorCCW_INP_DIS                (* (reg8 *) MotorCCW__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorCCW_LCD_COM_SEG            (* (reg8 *) MotorCCW__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorCCW_LCD_EN                 (* (reg8 *) MotorCCW__LCD_EN)
/* Slew Rate Control */
#define MotorCCW_SLW                    (* (reg8 *) MotorCCW__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorCCW_PRTDSI__CAPS_SEL       (* (reg8 *) MotorCCW__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorCCW_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorCCW__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorCCW_PRTDSI__OE_SEL0        (* (reg8 *) MotorCCW__PRTDSI__OE_SEL0) 
#define MotorCCW_PRTDSI__OE_SEL1        (* (reg8 *) MotorCCW__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorCCW_PRTDSI__OUT_SEL0       (* (reg8 *) MotorCCW__PRTDSI__OUT_SEL0) 
#define MotorCCW_PRTDSI__OUT_SEL1       (* (reg8 *) MotorCCW__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorCCW_PRTDSI__SYNC_OUT       (* (reg8 *) MotorCCW__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotorCCW__SIO_CFG)
    #define MotorCCW_SIO_HYST_EN        (* (reg8 *) MotorCCW__SIO_HYST_EN)
    #define MotorCCW_SIO_REG_HIFREQ     (* (reg8 *) MotorCCW__SIO_REG_HIFREQ)
    #define MotorCCW_SIO_CFG            (* (reg8 *) MotorCCW__SIO_CFG)
    #define MotorCCW_SIO_DIFF           (* (reg8 *) MotorCCW__SIO_DIFF)
#endif /* (MotorCCW__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotorCCW__INTSTAT)
    #define MotorCCW_INTSTAT            (* (reg8 *) MotorCCW__INTSTAT)
    #define MotorCCW_SNAP               (* (reg8 *) MotorCCW__SNAP)
    
	#define MotorCCW_0_INTTYPE_REG 		(* (reg8 *) MotorCCW__0__INTTYPE)
#endif /* (MotorCCW__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotorCCW_H */


/* [] END OF FILE */
