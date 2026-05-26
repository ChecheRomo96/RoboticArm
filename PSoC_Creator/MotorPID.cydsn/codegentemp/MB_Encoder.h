/*******************************************************************************
* File Name: MB_Encoder.h  
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

#if !defined(CY_PINS_MB_Encoder_H) /* Pins MB_Encoder_H */
#define CY_PINS_MB_Encoder_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MB_Encoder_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MB_Encoder__PORT == 15 && ((MB_Encoder__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MB_Encoder_Write(uint8 value);
void    MB_Encoder_SetDriveMode(uint8 mode);
uint8   MB_Encoder_ReadDataReg(void);
uint8   MB_Encoder_Read(void);
void    MB_Encoder_SetInterruptMode(uint16 position, uint16 mode);
uint8   MB_Encoder_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MB_Encoder_SetDriveMode() function.
     *  @{
     */
        #define MB_Encoder_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MB_Encoder_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MB_Encoder_DM_RES_UP          PIN_DM_RES_UP
        #define MB_Encoder_DM_RES_DWN         PIN_DM_RES_DWN
        #define MB_Encoder_DM_OD_LO           PIN_DM_OD_LO
        #define MB_Encoder_DM_OD_HI           PIN_DM_OD_HI
        #define MB_Encoder_DM_STRONG          PIN_DM_STRONG
        #define MB_Encoder_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MB_Encoder_MASK               MB_Encoder__MASK
#define MB_Encoder_SHIFT              MB_Encoder__SHIFT
#define MB_Encoder_WIDTH              2u

/* Interrupt constants */
#if defined(MB_Encoder__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MB_Encoder_SetInterruptMode() function.
     *  @{
     */
        #define MB_Encoder_INTR_NONE      (uint16)(0x0000u)
        #define MB_Encoder_INTR_RISING    (uint16)(0x0001u)
        #define MB_Encoder_INTR_FALLING   (uint16)(0x0002u)
        #define MB_Encoder_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MB_Encoder_INTR_MASK      (0x01u) 
#endif /* (MB_Encoder__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MB_Encoder_PS                     (* (reg8 *) MB_Encoder__PS)
/* Data Register */
#define MB_Encoder_DR                     (* (reg8 *) MB_Encoder__DR)
/* Port Number */
#define MB_Encoder_PRT_NUM                (* (reg8 *) MB_Encoder__PRT) 
/* Connect to Analog Globals */                                                  
#define MB_Encoder_AG                     (* (reg8 *) MB_Encoder__AG)                       
/* Analog MUX bux enable */
#define MB_Encoder_AMUX                   (* (reg8 *) MB_Encoder__AMUX) 
/* Bidirectional Enable */                                                        
#define MB_Encoder_BIE                    (* (reg8 *) MB_Encoder__BIE)
/* Bit-mask for Aliased Register Access */
#define MB_Encoder_BIT_MASK               (* (reg8 *) MB_Encoder__BIT_MASK)
/* Bypass Enable */
#define MB_Encoder_BYP                    (* (reg8 *) MB_Encoder__BYP)
/* Port wide control signals */                                                   
#define MB_Encoder_CTL                    (* (reg8 *) MB_Encoder__CTL)
/* Drive Modes */
#define MB_Encoder_DM0                    (* (reg8 *) MB_Encoder__DM0) 
#define MB_Encoder_DM1                    (* (reg8 *) MB_Encoder__DM1)
#define MB_Encoder_DM2                    (* (reg8 *) MB_Encoder__DM2) 
/* Input Buffer Disable Override */
#define MB_Encoder_INP_DIS                (* (reg8 *) MB_Encoder__INP_DIS)
/* LCD Common or Segment Drive */
#define MB_Encoder_LCD_COM_SEG            (* (reg8 *) MB_Encoder__LCD_COM_SEG)
/* Enable Segment LCD */
#define MB_Encoder_LCD_EN                 (* (reg8 *) MB_Encoder__LCD_EN)
/* Slew Rate Control */
#define MB_Encoder_SLW                    (* (reg8 *) MB_Encoder__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MB_Encoder_PRTDSI__CAPS_SEL       (* (reg8 *) MB_Encoder__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MB_Encoder_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MB_Encoder__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MB_Encoder_PRTDSI__OE_SEL0        (* (reg8 *) MB_Encoder__PRTDSI__OE_SEL0) 
#define MB_Encoder_PRTDSI__OE_SEL1        (* (reg8 *) MB_Encoder__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MB_Encoder_PRTDSI__OUT_SEL0       (* (reg8 *) MB_Encoder__PRTDSI__OUT_SEL0) 
#define MB_Encoder_PRTDSI__OUT_SEL1       (* (reg8 *) MB_Encoder__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MB_Encoder_PRTDSI__SYNC_OUT       (* (reg8 *) MB_Encoder__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MB_Encoder__SIO_CFG)
    #define MB_Encoder_SIO_HYST_EN        (* (reg8 *) MB_Encoder__SIO_HYST_EN)
    #define MB_Encoder_SIO_REG_HIFREQ     (* (reg8 *) MB_Encoder__SIO_REG_HIFREQ)
    #define MB_Encoder_SIO_CFG            (* (reg8 *) MB_Encoder__SIO_CFG)
    #define MB_Encoder_SIO_DIFF           (* (reg8 *) MB_Encoder__SIO_DIFF)
#endif /* (MB_Encoder__SIO_CFG) */

/* Interrupt Registers */
#if defined(MB_Encoder__INTSTAT)
    #define MB_Encoder_INTSTAT            (* (reg8 *) MB_Encoder__INTSTAT)
    #define MB_Encoder_SNAP               (* (reg8 *) MB_Encoder__SNAP)
    
	#define MB_Encoder_0_INTTYPE_REG 		(* (reg8 *) MB_Encoder__0__INTTYPE)
	#define MB_Encoder_1_INTTYPE_REG 		(* (reg8 *) MB_Encoder__1__INTTYPE)
#endif /* (MB_Encoder__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MB_Encoder_H */


/* [] END OF FILE */
