/*******************************************************************************
* File Name: MotorCW.h  
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

#if !defined(CY_PINS_MotorCW_H) /* Pins MotorCW_H */
#define CY_PINS_MotorCW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorCW_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotorCW__PORT == 15 && ((MotorCW__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotorCW_Write(uint8 value);
void    MotorCW_SetDriveMode(uint8 mode);
uint8   MotorCW_ReadDataReg(void);
uint8   MotorCW_Read(void);
void    MotorCW_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotorCW_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotorCW_SetDriveMode() function.
     *  @{
     */
        #define MotorCW_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotorCW_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotorCW_DM_RES_UP          PIN_DM_RES_UP
        #define MotorCW_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotorCW_DM_OD_LO           PIN_DM_OD_LO
        #define MotorCW_DM_OD_HI           PIN_DM_OD_HI
        #define MotorCW_DM_STRONG          PIN_DM_STRONG
        #define MotorCW_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotorCW_MASK               MotorCW__MASK
#define MotorCW_SHIFT              MotorCW__SHIFT
#define MotorCW_WIDTH              1u

/* Interrupt constants */
#if defined(MotorCW__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotorCW_SetInterruptMode() function.
     *  @{
     */
        #define MotorCW_INTR_NONE      (uint16)(0x0000u)
        #define MotorCW_INTR_RISING    (uint16)(0x0001u)
        #define MotorCW_INTR_FALLING   (uint16)(0x0002u)
        #define MotorCW_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotorCW_INTR_MASK      (0x01u) 
#endif /* (MotorCW__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorCW_PS                     (* (reg8 *) MotorCW__PS)
/* Data Register */
#define MotorCW_DR                     (* (reg8 *) MotorCW__DR)
/* Port Number */
#define MotorCW_PRT_NUM                (* (reg8 *) MotorCW__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorCW_AG                     (* (reg8 *) MotorCW__AG)                       
/* Analog MUX bux enable */
#define MotorCW_AMUX                   (* (reg8 *) MotorCW__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorCW_BIE                    (* (reg8 *) MotorCW__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorCW_BIT_MASK               (* (reg8 *) MotorCW__BIT_MASK)
/* Bypass Enable */
#define MotorCW_BYP                    (* (reg8 *) MotorCW__BYP)
/* Port wide control signals */                                                   
#define MotorCW_CTL                    (* (reg8 *) MotorCW__CTL)
/* Drive Modes */
#define MotorCW_DM0                    (* (reg8 *) MotorCW__DM0) 
#define MotorCW_DM1                    (* (reg8 *) MotorCW__DM1)
#define MotorCW_DM2                    (* (reg8 *) MotorCW__DM2) 
/* Input Buffer Disable Override */
#define MotorCW_INP_DIS                (* (reg8 *) MotorCW__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorCW_LCD_COM_SEG            (* (reg8 *) MotorCW__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorCW_LCD_EN                 (* (reg8 *) MotorCW__LCD_EN)
/* Slew Rate Control */
#define MotorCW_SLW                    (* (reg8 *) MotorCW__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorCW_PRTDSI__CAPS_SEL       (* (reg8 *) MotorCW__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorCW_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorCW__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorCW_PRTDSI__OE_SEL0        (* (reg8 *) MotorCW__PRTDSI__OE_SEL0) 
#define MotorCW_PRTDSI__OE_SEL1        (* (reg8 *) MotorCW__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorCW_PRTDSI__OUT_SEL0       (* (reg8 *) MotorCW__PRTDSI__OUT_SEL0) 
#define MotorCW_PRTDSI__OUT_SEL1       (* (reg8 *) MotorCW__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorCW_PRTDSI__SYNC_OUT       (* (reg8 *) MotorCW__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotorCW__SIO_CFG)
    #define MotorCW_SIO_HYST_EN        (* (reg8 *) MotorCW__SIO_HYST_EN)
    #define MotorCW_SIO_REG_HIFREQ     (* (reg8 *) MotorCW__SIO_REG_HIFREQ)
    #define MotorCW_SIO_CFG            (* (reg8 *) MotorCW__SIO_CFG)
    #define MotorCW_SIO_DIFF           (* (reg8 *) MotorCW__SIO_DIFF)
#endif /* (MotorCW__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotorCW__INTSTAT)
    #define MotorCW_INTSTAT            (* (reg8 *) MotorCW__INTSTAT)
    #define MotorCW_SNAP               (* (reg8 *) MotorCW__SNAP)
    
	#define MotorCW_0_INTTYPE_REG 		(* (reg8 *) MotorCW__0__INTTYPE)
#endif /* (MotorCW__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotorCW_H */


/* [] END OF FILE */
