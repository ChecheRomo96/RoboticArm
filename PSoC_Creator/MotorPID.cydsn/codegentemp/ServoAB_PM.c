/*******************************************************************************
* File Name: ServoAB_PM.c
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

#include "ServoAB.h"

static ServoAB_backupStruct ServoAB_backup;


/*******************************************************************************
* Function Name: ServoAB_SaveConfig
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
*  ServoAB_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ServoAB_SaveConfig(void) 
{

    #if(!ServoAB_UsingFixedFunction)
        #if(!ServoAB_PWMModeIsCenterAligned)
            ServoAB_backup.PWMPeriod = ServoAB_ReadPeriod();
        #endif /* (!ServoAB_PWMModeIsCenterAligned) */
        ServoAB_backup.PWMUdb = ServoAB_ReadCounter();
        #if (ServoAB_UseStatus)
            ServoAB_backup.InterruptMaskValue = ServoAB_STATUS_MASK;
        #endif /* (ServoAB_UseStatus) */

        #if(ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_256_CLOCKS || \
            ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_2_4_CLOCKS)
            ServoAB_backup.PWMdeadBandValue = ServoAB_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(ServoAB_KillModeMinTime)
             ServoAB_backup.PWMKillCounterPeriod = ServoAB_ReadKillTime();
        #endif /* (ServoAB_KillModeMinTime) */

        #if(ServoAB_UseControl)
            ServoAB_backup.PWMControlRegister = ServoAB_ReadControlRegister();
        #endif /* (ServoAB_UseControl) */
    #endif  /* (!ServoAB_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoAB_RestoreConfig
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
*  ServoAB_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ServoAB_RestoreConfig(void) 
{
        #if(!ServoAB_UsingFixedFunction)
            #if(!ServoAB_PWMModeIsCenterAligned)
                ServoAB_WritePeriod(ServoAB_backup.PWMPeriod);
            #endif /* (!ServoAB_PWMModeIsCenterAligned) */

            ServoAB_WriteCounter(ServoAB_backup.PWMUdb);

            #if (ServoAB_UseStatus)
                ServoAB_STATUS_MASK = ServoAB_backup.InterruptMaskValue;
            #endif /* (ServoAB_UseStatus) */

            #if(ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_256_CLOCKS || \
                ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_2_4_CLOCKS)
                ServoAB_WriteDeadTime(ServoAB_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(ServoAB_KillModeMinTime)
                ServoAB_WriteKillTime(ServoAB_backup.PWMKillCounterPeriod);
            #endif /* (ServoAB_KillModeMinTime) */

            #if(ServoAB_UseControl)
                ServoAB_WriteControlRegister(ServoAB_backup.PWMControlRegister);
            #endif /* (ServoAB_UseControl) */
        #endif  /* (!ServoAB_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ServoAB_Sleep
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
*  ServoAB_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ServoAB_Sleep(void) 
{
    #if(ServoAB_UseControl)
        if(ServoAB_CTRL_ENABLE == (ServoAB_CONTROL & ServoAB_CTRL_ENABLE))
        {
            /*Component is enabled */
            ServoAB_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ServoAB_backup.PWMEnableState = 0u;
        }
    #endif /* (ServoAB_UseControl) */

    /* Stop component */
    ServoAB_Stop();

    /* Save registers configuration */
    ServoAB_SaveConfig();
}


/*******************************************************************************
* Function Name: ServoAB_Wakeup
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
*  ServoAB_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ServoAB_Wakeup(void) 
{
     /* Restore registers values */
    ServoAB_RestoreConfig();

    if(ServoAB_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ServoAB_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
