/*******************************************************************************
* File Name: ServoCD_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ServoCD.h"

static ServoCD_backupStruct ServoCD_backup;


/*******************************************************************************
* Function Name: ServoCD_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoCD_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ServoCD_SaveConfig(void) 
{

    #if(!ServoCD_UsingFixedFunction)
        #if(!ServoCD_PWMModeIsCenterAligned)
            ServoCD_backup.PWMPeriod = ServoCD_ReadPeriod();
        #endif /* (!ServoCD_PWMModeIsCenterAligned) */
        ServoCD_backup.PWMUdb = ServoCD_ReadCounter();
        #if (ServoCD_UseStatus)
            ServoCD_backup.InterruptMaskValue = ServoCD_STATUS_MASK;
        #endif /* (ServoCD_UseStatus) */

        #if(ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_256_CLOCKS || \
            ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_2_4_CLOCKS)
            ServoCD_backup.PWMdeadBandValue = ServoCD_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(ServoCD_KillModeMinTime)
             ServoCD_backup.PWMKillCounterPeriod = ServoCD_ReadKillTime();
        #endif /* (ServoCD_KillModeMinTime) */

        #if(ServoCD_UseControl)
            ServoCD_backup.PWMControlRegister = ServoCD_ReadControlRegister();
        #endif /* (ServoCD_UseControl) */
    #endif  /* (!ServoCD_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCD_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoCD_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ServoCD_RestoreConfig(void) 
{
        #if(!ServoCD_UsingFixedFunction)
            #if(!ServoCD_PWMModeIsCenterAligned)
                ServoCD_WritePeriod(ServoCD_backup.PWMPeriod);
            #endif /* (!ServoCD_PWMModeIsCenterAligned) */

            ServoCD_WriteCounter(ServoCD_backup.PWMUdb);

            #if (ServoCD_UseStatus)
                ServoCD_STATUS_MASK = ServoCD_backup.InterruptMaskValue;
            #endif /* (ServoCD_UseStatus) */

            #if(ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_256_CLOCKS || \
                ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_2_4_CLOCKS)
                ServoCD_WriteDeadTime(ServoCD_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(ServoCD_KillModeMinTime)
                ServoCD_WriteKillTime(ServoCD_backup.PWMKillCounterPeriod);
            #endif /* (ServoCD_KillModeMinTime) */

            #if(ServoCD_UseControl)
                ServoCD_WriteControlRegister(ServoCD_backup.PWMControlRegister);
            #endif /* (ServoCD_UseControl) */
        #endif  /* (!ServoCD_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ServoCD_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoCD_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ServoCD_Sleep(void) 
{
    #if(ServoCD_UseControl)
        if(ServoCD_CTRL_ENABLE == (ServoCD_CONTROL & ServoCD_CTRL_ENABLE))
        {
            /*Component is enabled */
            ServoCD_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ServoCD_backup.PWMEnableState = 0u;
        }
    #endif /* (ServoCD_UseControl) */

    /* Stop component */
    ServoCD_Stop();

    /* Save registers configuration */
    ServoCD_SaveConfig();
}


/*******************************************************************************
* Function Name: ServoCD_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoCD_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ServoCD_Wakeup(void) 
{
     /* Restore registers values */
    ServoCD_RestoreConfig();

    if(ServoCD_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ServoCD_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
