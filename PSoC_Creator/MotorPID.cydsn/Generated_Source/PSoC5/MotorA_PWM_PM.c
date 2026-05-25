/*******************************************************************************
* File Name: MotorA_PWM_PM.c
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

#include "MotorA_PWM.h"

static MotorA_PWM_backupStruct MotorA_PWM_backup;


/*******************************************************************************
* Function Name: MotorA_PWM_SaveConfig
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
*  MotorA_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MotorA_PWM_SaveConfig(void) 
{

    #if(!MotorA_PWM_UsingFixedFunction)
        #if(!MotorA_PWM_PWMModeIsCenterAligned)
            MotorA_PWM_backup.PWMPeriod = MotorA_PWM_ReadPeriod();
        #endif /* (!MotorA_PWM_PWMModeIsCenterAligned) */
        MotorA_PWM_backup.PWMUdb = MotorA_PWM_ReadCounter();
        #if (MotorA_PWM_UseStatus)
            MotorA_PWM_backup.InterruptMaskValue = MotorA_PWM_STATUS_MASK;
        #endif /* (MotorA_PWM_UseStatus) */

        #if(MotorA_PWM_DeadBandMode == MotorA_PWM__B_PWM__DBM_256_CLOCKS || \
            MotorA_PWM_DeadBandMode == MotorA_PWM__B_PWM__DBM_2_4_CLOCKS)
            MotorA_PWM_backup.PWMdeadBandValue = MotorA_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MotorA_PWM_KillModeMinTime)
             MotorA_PWM_backup.PWMKillCounterPeriod = MotorA_PWM_ReadKillTime();
        #endif /* (MotorA_PWM_KillModeMinTime) */

        #if(MotorA_PWM_UseControl)
            MotorA_PWM_backup.PWMControlRegister = MotorA_PWM_ReadControlRegister();
        #endif /* (MotorA_PWM_UseControl) */
    #endif  /* (!MotorA_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorA_PWM_RestoreConfig
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
*  MotorA_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorA_PWM_RestoreConfig(void) 
{
        #if(!MotorA_PWM_UsingFixedFunction)
            #if(!MotorA_PWM_PWMModeIsCenterAligned)
                MotorA_PWM_WritePeriod(MotorA_PWM_backup.PWMPeriod);
            #endif /* (!MotorA_PWM_PWMModeIsCenterAligned) */

            MotorA_PWM_WriteCounter(MotorA_PWM_backup.PWMUdb);

            #if (MotorA_PWM_UseStatus)
                MotorA_PWM_STATUS_MASK = MotorA_PWM_backup.InterruptMaskValue;
            #endif /* (MotorA_PWM_UseStatus) */

            #if(MotorA_PWM_DeadBandMode == MotorA_PWM__B_PWM__DBM_256_CLOCKS || \
                MotorA_PWM_DeadBandMode == MotorA_PWM__B_PWM__DBM_2_4_CLOCKS)
                MotorA_PWM_WriteDeadTime(MotorA_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MotorA_PWM_KillModeMinTime)
                MotorA_PWM_WriteKillTime(MotorA_PWM_backup.PWMKillCounterPeriod);
            #endif /* (MotorA_PWM_KillModeMinTime) */

            #if(MotorA_PWM_UseControl)
                MotorA_PWM_WriteControlRegister(MotorA_PWM_backup.PWMControlRegister);
            #endif /* (MotorA_PWM_UseControl) */
        #endif  /* (!MotorA_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MotorA_PWM_Sleep
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
*  MotorA_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorA_PWM_Sleep(void) 
{
    #if(MotorA_PWM_UseControl)
        if(MotorA_PWM_CTRL_ENABLE == (MotorA_PWM_CONTROL & MotorA_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            MotorA_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MotorA_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (MotorA_PWM_UseControl) */

    /* Stop component */
    MotorA_PWM_Stop();

    /* Save registers configuration */
    MotorA_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorA_PWM_Wakeup
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
*  MotorA_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorA_PWM_Wakeup(void) 
{
     /* Restore registers values */
    MotorA_PWM_RestoreConfig();

    if(MotorA_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MotorA_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
