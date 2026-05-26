/*******************************************************************************
* File Name: MotorB_QuadDec_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

#include "MotorB_QuadDec.h"

static MotorB_QuadDec_BACKUP_STRUCT MotorB_QuadDec_backup = {0u};


/*******************************************************************************
* Function Name: MotorB_QuadDec_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorB_QuadDec_SaveConfig(void) 
{
    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT)
        MotorB_QuadDec_Cnt8_SaveConfig();
    #else 
        /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
         */
        MotorB_QuadDec_Cnt16_SaveConfig();
    #endif /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorB_QuadDec_RestoreConfig(void) 
{
    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT)
        MotorB_QuadDec_Cnt8_RestoreConfig();
    #else 
        /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT) 
         */
        MotorB_QuadDec_Cnt16_RestoreConfig();
    #endif /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MotorB_QuadDec_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MotorB_QuadDec_Sleep(void) 
{
    if (0u != (MotorB_QuadDec_SR_AUX_CONTROL & MotorB_QuadDec_INTERRUPTS_ENABLE))
    {
        MotorB_QuadDec_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        MotorB_QuadDec_backup.enableState = 0u;
    }

    MotorB_QuadDec_Stop();
    MotorB_QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MotorB_QuadDec_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void MotorB_QuadDec_Wakeup(void) 
{
    MotorB_QuadDec_RestoreConfig();

    if (MotorB_QuadDec_backup.enableState != 0u)
    {
        #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT)
            MotorB_QuadDec_Cnt8_Enable();
        #else 
            /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT) || 
            *  (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT) 
            */
            MotorB_QuadDec_Cnt16_Enable();
        #endif /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        MotorB_QuadDec_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

