/*******************************************************************************
* File Name: MotorB_QuadDec_Cnt16_PM.c  
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

#include "MotorB_QuadDec_Cnt16.h"

static MotorB_QuadDec_Cnt16_backupStruct MotorB_QuadDec_Cnt16_backup;


/*******************************************************************************
* Function Name: MotorB_QuadDec_Cnt16_SaveConfig
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
*  MotorB_QuadDec_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void MotorB_QuadDec_Cnt16_SaveConfig(void) 
{
    #if (!MotorB_QuadDec_Cnt16_UsingFixedFunction)

        MotorB_QuadDec_Cnt16_backup.CounterUdb = MotorB_QuadDec_Cnt16_ReadCounter();

        #if(!MotorB_QuadDec_Cnt16_ControlRegRemoved)
            MotorB_QuadDec_Cnt16_backup.CounterControlRegister = MotorB_QuadDec_Cnt16_ReadControlRegister();
        #endif /* (!MotorB_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!MotorB_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Cnt16_RestoreConfig
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
*  MotorB_QuadDec_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorB_QuadDec_Cnt16_RestoreConfig(void) 
{      
    #if (!MotorB_QuadDec_Cnt16_UsingFixedFunction)

       MotorB_QuadDec_Cnt16_WriteCounter(MotorB_QuadDec_Cnt16_backup.CounterUdb);

        #if(!MotorB_QuadDec_Cnt16_ControlRegRemoved)
            MotorB_QuadDec_Cnt16_WriteControlRegister(MotorB_QuadDec_Cnt16_backup.CounterControlRegister);
        #endif /* (!MotorB_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!MotorB_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Cnt16_Sleep
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
*  MotorB_QuadDec_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorB_QuadDec_Cnt16_Sleep(void) 
{
    #if(!MotorB_QuadDec_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(MotorB_QuadDec_Cnt16_CTRL_ENABLE == (MotorB_QuadDec_Cnt16_CONTROL & MotorB_QuadDec_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            MotorB_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            MotorB_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        MotorB_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        if(MotorB_QuadDec_Cnt16_backup.CounterEnableState != 0u)
        {
            MotorB_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!MotorB_QuadDec_Cnt16_ControlRegRemoved) */
    
    MotorB_QuadDec_Cnt16_Stop();
    MotorB_QuadDec_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Cnt16_Wakeup
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
*  MotorB_QuadDec_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorB_QuadDec_Cnt16_Wakeup(void) 
{
    MotorB_QuadDec_Cnt16_RestoreConfig();
    #if(!MotorB_QuadDec_Cnt16_ControlRegRemoved)
        if(MotorB_QuadDec_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            MotorB_QuadDec_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!MotorB_QuadDec_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
