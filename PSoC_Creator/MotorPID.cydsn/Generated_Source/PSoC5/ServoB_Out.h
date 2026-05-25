/*******************************************************************************
* File Name: ServoB_Out.h  
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

#if !defined(CY_PINS_ServoB_Out_H) /* Pins ServoB_Out_H */
#define CY_PINS_ServoB_Out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ServoB_Out_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ServoB_Out__PORT == 15 && ((ServoB_Out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ServoB_Out_Write(uint8 value);
void    ServoB_Out_SetDriveMode(uint8 mode);
uint8   ServoB_Out_ReadDataReg(void);
uint8   ServoB_Out_Read(void);
void    ServoB_Out_SetInterruptMode(uint16 position, uint16 mode);
uint8   ServoB_Out_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ServoB_Out_SetDriveMode() function.
     *  @{
     */
        #define ServoB_Out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ServoB_Out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ServoB_Out_DM_RES_UP          PIN_DM_RES_UP
        #define ServoB_Out_DM_RES_DWN         PIN_DM_RES_DWN
        #define ServoB_Out_DM_OD_LO           PIN_DM_OD_LO
        #define ServoB_Out_DM_OD_HI           PIN_DM_OD_HI
        #define ServoB_Out_DM_STRONG          PIN_DM_STRONG
        #define ServoB_Out_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ServoB_Out_MASK               ServoB_Out__MASK
#define ServoB_Out_SHIFT              ServoB_Out__SHIFT
#define ServoB_Out_WIDTH              1u

/* Interrupt constants */
#if defined(ServoB_Out__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ServoB_Out_SetInterruptMode() function.
     *  @{
     */
        #define ServoB_Out_INTR_NONE      (uint16)(0x0000u)
        #define ServoB_Out_INTR_RISING    (uint16)(0x0001u)
        #define ServoB_Out_INTR_FALLING   (uint16)(0x0002u)
        #define ServoB_Out_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ServoB_Out_INTR_MASK      (0x01u) 
#endif /* (ServoB_Out__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ServoB_Out_PS                     (* (reg8 *) ServoB_Out__PS)
/* Data Register */
#define ServoB_Out_DR                     (* (reg8 *) ServoB_Out__DR)
/* Port Number */
#define ServoB_Out_PRT_NUM                (* (reg8 *) ServoB_Out__PRT) 
/* Connect to Analog Globals */                                                  
#define ServoB_Out_AG                     (* (reg8 *) ServoB_Out__AG)                       
/* Analog MUX bux enable */
#define ServoB_Out_AMUX                   (* (reg8 *) ServoB_Out__AMUX) 
/* Bidirectional Enable */                                                        
#define ServoB_Out_BIE                    (* (reg8 *) ServoB_Out__BIE)
/* Bit-mask for Aliased Register Access */
#define ServoB_Out_BIT_MASK               (* (reg8 *) ServoB_Out__BIT_MASK)
/* Bypass Enable */
#define ServoB_Out_BYP                    (* (reg8 *) ServoB_Out__BYP)
/* Port wide control signals */                                                   
#define ServoB_Out_CTL                    (* (reg8 *) ServoB_Out__CTL)
/* Drive Modes */
#define ServoB_Out_DM0                    (* (reg8 *) ServoB_Out__DM0) 
#define ServoB_Out_DM1                    (* (reg8 *) ServoB_Out__DM1)
#define ServoB_Out_DM2                    (* (reg8 *) ServoB_Out__DM2) 
/* Input Buffer Disable Override */
#define ServoB_Out_INP_DIS                (* (reg8 *) ServoB_Out__INP_DIS)
/* LCD Common or Segment Drive */
#define ServoB_Out_LCD_COM_SEG            (* (reg8 *) ServoB_Out__LCD_COM_SEG)
/* Enable Segment LCD */
#define ServoB_Out_LCD_EN                 (* (reg8 *) ServoB_Out__LCD_EN)
/* Slew Rate Control */
#define ServoB_Out_SLW                    (* (reg8 *) ServoB_Out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ServoB_Out_PRTDSI__CAPS_SEL       (* (reg8 *) ServoB_Out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ServoB_Out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ServoB_Out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ServoB_Out_PRTDSI__OE_SEL0        (* (reg8 *) ServoB_Out__PRTDSI__OE_SEL0) 
#define ServoB_Out_PRTDSI__OE_SEL1        (* (reg8 *) ServoB_Out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ServoB_Out_PRTDSI__OUT_SEL0       (* (reg8 *) ServoB_Out__PRTDSI__OUT_SEL0) 
#define ServoB_Out_PRTDSI__OUT_SEL1       (* (reg8 *) ServoB_Out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ServoB_Out_PRTDSI__SYNC_OUT       (* (reg8 *) ServoB_Out__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ServoB_Out__SIO_CFG)
    #define ServoB_Out_SIO_HYST_EN        (* (reg8 *) ServoB_Out__SIO_HYST_EN)
    #define ServoB_Out_SIO_REG_HIFREQ     (* (reg8 *) ServoB_Out__SIO_REG_HIFREQ)
    #define ServoB_Out_SIO_CFG            (* (reg8 *) ServoB_Out__SIO_CFG)
    #define ServoB_Out_SIO_DIFF           (* (reg8 *) ServoB_Out__SIO_DIFF)
#endif /* (ServoB_Out__SIO_CFG) */

/* Interrupt Registers */
#if defined(ServoB_Out__INTSTAT)
    #define ServoB_Out_INTSTAT            (* (reg8 *) ServoB_Out__INTSTAT)
    #define ServoB_Out_SNAP               (* (reg8 *) ServoB_Out__SNAP)
    
	#define ServoB_Out_0_INTTYPE_REG 		(* (reg8 *) ServoB_Out__0__INTTYPE)
#endif /* (ServoB_Out__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ServoB_Out_H */


/* [] END OF FILE */
