/*******************************************************************************
* File Name: usCounter_PM.c  
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

#include "usCounter.h"

static usCounter_backupStruct usCounter_backup;


/*******************************************************************************
* Function Name: usCounter_SaveConfig
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
*  usCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void usCounter_SaveConfig(void) 
{
    #if (!usCounter_UsingFixedFunction)

        usCounter_backup.CounterUdb = usCounter_ReadCounter();

        #if(!usCounter_ControlRegRemoved)
            usCounter_backup.CounterControlRegister = usCounter_ReadControlRegister();
        #endif /* (!usCounter_ControlRegRemoved) */

    #endif /* (!usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_RestoreConfig
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
*  usCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void usCounter_RestoreConfig(void) 
{      
    #if (!usCounter_UsingFixedFunction)

       usCounter_WriteCounter(usCounter_backup.CounterUdb);

        #if(!usCounter_ControlRegRemoved)
            usCounter_WriteControlRegister(usCounter_backup.CounterControlRegister);
        #endif /* (!usCounter_ControlRegRemoved) */

    #endif /* (!usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_Sleep
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
*  usCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void usCounter_Sleep(void) 
{
    #if(!usCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(usCounter_CTRL_ENABLE == (usCounter_CONTROL & usCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            usCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            usCounter_backup.CounterEnableState = 0u;
        }
    #else
        usCounter_backup.CounterEnableState = 1u;
        if(usCounter_backup.CounterEnableState != 0u)
        {
            usCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!usCounter_ControlRegRemoved) */
    
    usCounter_Stop();
    usCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: usCounter_Wakeup
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
*  usCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void usCounter_Wakeup(void) 
{
    usCounter_RestoreConfig();
    #if(!usCounter_ControlRegRemoved)
        if(usCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            usCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!usCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
