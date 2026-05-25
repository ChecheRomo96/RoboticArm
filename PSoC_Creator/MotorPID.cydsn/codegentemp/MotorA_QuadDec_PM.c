/*******************************************************************************
* File Name: MotorA_QuadDec_PM.c
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

#include "MotorA_QuadDec.h"

static MotorA_QuadDec_BACKUP_STRUCT MotorA_QuadDec_backup = {0u};


/*******************************************************************************
* Function Name: MotorA_QuadDec_SaveConfig
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
void MotorA_QuadDec_SaveConfig(void) 
{
    #if (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT)
        MotorA_QuadDec_Cnt8_SaveConfig();
    #else 
        /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT)
         */
        MotorA_QuadDec_Cnt16_SaveConfig();
    #endif /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: MotorA_QuadDec_RestoreConfig
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
void MotorA_QuadDec_RestoreConfig(void) 
{
    #if (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT)
        MotorA_QuadDec_Cnt8_RestoreConfig();
    #else 
        /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT) 
         */
        MotorA_QuadDec_Cnt16_RestoreConfig();
    #endif /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: MotorA_QuadDec_Sleep
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
*  MotorA_QuadDec_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MotorA_QuadDec_Sleep(void) 
{
    if (0u != (MotorA_QuadDec_SR_AUX_CONTROL & MotorA_QuadDec_INTERRUPTS_ENABLE))
    {
        MotorA_QuadDec_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        MotorA_QuadDec_backup.enableState = 0u;
    }

    MotorA_QuadDec_Stop();
    MotorA_QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorA_QuadDec_Wakeup
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
*  MotorA_QuadDec_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void MotorA_QuadDec_Wakeup(void) 
{
    MotorA_QuadDec_RestoreConfig();

    if (MotorA_QuadDec_backup.enableState != 0u)
    {
        #if (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT)
            MotorA_QuadDec_Cnt8_Enable();
        #else 
            /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_16_BIT) || 
            *  (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_32_BIT) 
            */
            MotorA_QuadDec_Cnt16_Enable();
        #endif /* (MotorA_QuadDec_COUNTER_SIZE == MotorA_QuadDec_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        MotorA_QuadDec_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

