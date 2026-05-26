/*******************************************************************************
* File Name: MotorB_PWM_PM.c
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

#include "MotorB_PWM.h"

static MotorB_PWM_backupStruct MotorB_PWM_backup;


/*******************************************************************************
* Function Name: MotorB_PWM_SaveConfig
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
*  MotorB_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MotorB_PWM_SaveConfig(void) 
{

    #if(!MotorB_PWM_UsingFixedFunction)
        #if(!MotorB_PWM_PWMModeIsCenterAligned)
            MotorB_PWM_backup.PWMPeriod = MotorB_PWM_ReadPeriod();
        #endif /* (!MotorB_PWM_PWMModeIsCenterAligned) */
        MotorB_PWM_backup.PWMUdb = MotorB_PWM_ReadCounter();
        #if (MotorB_PWM_UseStatus)
            MotorB_PWM_backup.InterruptMaskValue = MotorB_PWM_STATUS_MASK;
        #endif /* (MotorB_PWM_UseStatus) */

        #if(MotorB_PWM_DeadBandMode == MotorB_PWM__B_PWM__DBM_256_CLOCKS || \
            MotorB_PWM_DeadBandMode == MotorB_PWM__B_PWM__DBM_2_4_CLOCKS)
            MotorB_PWM_backup.PWMdeadBandValue = MotorB_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MotorB_PWM_KillModeMinTime)
             MotorB_PWM_backup.PWMKillCounterPeriod = MotorB_PWM_ReadKillTime();
        #endif /* (MotorB_PWM_KillModeMinTime) */

        #if(MotorB_PWM_UseControl)
            MotorB_PWM_backup.PWMControlRegister = MotorB_PWM_ReadControlRegister();
        #endif /* (MotorB_PWM_UseControl) */
    #endif  /* (!MotorB_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorB_PWM_RestoreConfig
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
*  MotorB_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorB_PWM_RestoreConfig(void) 
{
        #if(!MotorB_PWM_UsingFixedFunction)
            #if(!MotorB_PWM_PWMModeIsCenterAligned)
                MotorB_PWM_WritePeriod(MotorB_PWM_backup.PWMPeriod);
            #endif /* (!MotorB_PWM_PWMModeIsCenterAligned) */

            MotorB_PWM_WriteCounter(MotorB_PWM_backup.PWMUdb);

            #if (MotorB_PWM_UseStatus)
                MotorB_PWM_STATUS_MASK = MotorB_PWM_backup.InterruptMaskValue;
            #endif /* (MotorB_PWM_UseStatus) */

            #if(MotorB_PWM_DeadBandMode == MotorB_PWM__B_PWM__DBM_256_CLOCKS || \
                MotorB_PWM_DeadBandMode == MotorB_PWM__B_PWM__DBM_2_4_CLOCKS)
                MotorB_PWM_WriteDeadTime(MotorB_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MotorB_PWM_KillModeMinTime)
                MotorB_PWM_WriteKillTime(MotorB_PWM_backup.PWMKillCounterPeriod);
            #endif /* (MotorB_PWM_KillModeMinTime) */

            #if(MotorB_PWM_UseControl)
                MotorB_PWM_WriteControlRegister(MotorB_PWM_backup.PWMControlRegister);
            #endif /* (MotorB_PWM_UseControl) */
        #endif  /* (!MotorB_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MotorB_PWM_Sleep
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
*  MotorB_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorB_PWM_Sleep(void) 
{
    #if(MotorB_PWM_UseControl)
        if(MotorB_PWM_CTRL_ENABLE == (MotorB_PWM_CONTROL & MotorB_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            MotorB_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MotorB_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (MotorB_PWM_UseControl) */

    /* Stop component */
    MotorB_PWM_Stop();

    /* Save registers configuration */
    MotorB_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorB_PWM_Wakeup
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
*  MotorB_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorB_PWM_Wakeup(void) 
{
     /* Restore registers values */
    MotorB_PWM_RestoreConfig();

    if(MotorB_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MotorB_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
