/*******************************************************************************
* File Name: MotorA_QuadDec_Cnt16_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MotorA_QuadDec_Cnt16.h"

static MotorA_QuadDec_Cnt16_backupStruct MotorA_QuadDec_Cnt16_backup;


/*******************************************************************************
* Function Name: MotorA_QuadDec_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  MotorA_QuadDec_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void MotorA_QuadDec_Cnt16_SaveConfig(void) 
{
    #if (!MotorA_QuadDec_Cnt16_UsingFixedFunction)

        MotorA_QuadDec_Cnt16_backup.CounterUdb = MotorA_QuadDec_Cnt16_ReadCounter();

        #if(!MotorA_QuadDec_Cnt16_ControlRegRemoved)
            MotorA_QuadDec_Cnt16_backup.CounterControlRegister = MotorA_QuadDec_Cnt16_ReadControlRegister();
        #endif /* (!MotorA_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!MotorA_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorA_QuadDec_Cnt16_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  MotorA_QuadDec_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorA_QuadDec_Cnt16_RestoreConfig(void) 
{      
    #if (!MotorA_QuadDec_Cnt16_UsingFixedFunction)

       MotorA_QuadDec_Cnt16_WriteCounter(MotorA_QuadDec_Cnt16_backup.CounterUdb);

        #if(!MotorA_QuadDec_Cnt16_ControlRegRemoved)
            MotorA_QuadDec_Cnt16_WriteControlRegister(MotorA_QuadDec_Cnt16_backup.CounterControlRegister);
        #endif /* (!MotorA_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!MotorA_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorA_QuadDec_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  MotorA_QuadDec_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorA_QuadDec_Cnt16_Sleep(void) 
{
    #if(!MotorA_QuadDec_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(MotorA_QuadDec_Cnt16_CTRL_ENABLE == (MotorA_QuadDec_Cnt16_CONTROL & MotorA_QuadDec_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            MotorA_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            MotorA_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        MotorA_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        if(MotorA_QuadDec_Cnt16_backup.CounterEnableState != 0u)
        {
            MotorA_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!MotorA_QuadDec_Cnt16_ControlRegRemoved) */
    
    MotorA_QuadDec_Cnt16_Stop();
    MotorA_QuadDec_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorA_QuadDec_Cnt16_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  MotorA_QuadDec_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorA_QuadDec_Cnt16_Wakeup(void) 
{
    MotorA_QuadDec_Cnt16_RestoreConfig();
    #if(!MotorA_QuadDec_Cnt16_ControlRegRemoved)
        if(MotorA_QuadDec_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            MotorA_QuadDec_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!MotorA_QuadDec_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
