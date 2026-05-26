/*******************************************************************************
* File Name: ServoCD.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "ServoCD.h"

/* Error message for removed <resource> through optimization */
#ifdef ServoCD_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* ServoCD_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 ServoCD_initVar = 0u;


/*******************************************************************************
* Function Name: ServoCD_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoCD_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ServoCD_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(ServoCD_initVar == 0u)
    {
        ServoCD_Init();
        ServoCD_initVar = 1u;
    }
    ServoCD_Enable();

}


/*******************************************************************************
* Function Name: ServoCD_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  ServoCD_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ServoCD_Init(void) 
{
    #if (ServoCD_UsingFixedFunction || ServoCD_UseControl)
        uint8 ctrl;
    #endif /* (ServoCD_UsingFixedFunction || ServoCD_UseControl) */

    #if(!ServoCD_UsingFixedFunction)
        #if(ServoCD_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 ServoCD_interruptState;
        #endif /* (ServoCD_UseStatus) */
    #endif /* (!ServoCD_UsingFixedFunction) */

    #if (ServoCD_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        ServoCD_CONTROL |= ServoCD_CFG0_MODE;
        #if (ServoCD_DeadBand2_4)
            ServoCD_CONTROL |= ServoCD_CFG0_DB;
        #endif /* (ServoCD_DeadBand2_4) */

        ctrl = ServoCD_CONTROL3 & ((uint8 )(~ServoCD_CTRL_CMPMODE1_MASK));
        ServoCD_CONTROL3 = ctrl | ServoCD_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        ServoCD_RT1 &= ((uint8)(~ServoCD_RT1_MASK));
        ServoCD_RT1 |= ServoCD_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        ServoCD_RT1 &= ((uint8)(~ServoCD_SYNCDSI_MASK));
        ServoCD_RT1 |= ServoCD_SYNCDSI_EN;

    #elif (ServoCD_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = ServoCD_CONTROL & ((uint8)(~ServoCD_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~ServoCD_CTRL_CMPMODE1_MASK));
        ServoCD_CONTROL = ctrl | ServoCD_DEFAULT_COMPARE2_MODE |
                                   ServoCD_DEFAULT_COMPARE1_MODE;
    #endif /* (ServoCD_UsingFixedFunction) */

    #if (!ServoCD_UsingFixedFunction)
        #if (ServoCD_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            ServoCD_AUX_CONTROLDP0 |= (ServoCD_AUX_CTRL_FIFO0_CLR);
        #else /* (ServoCD_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            ServoCD_AUX_CONTROLDP0 |= (ServoCD_AUX_CTRL_FIFO0_CLR);
            ServoCD_AUX_CONTROLDP1 |= (ServoCD_AUX_CTRL_FIFO0_CLR);
        #endif /* (ServoCD_Resolution == 8) */

        ServoCD_WriteCounter(ServoCD_INIT_PERIOD_VALUE);
    #endif /* (!ServoCD_UsingFixedFunction) */

    ServoCD_WritePeriod(ServoCD_INIT_PERIOD_VALUE);

        #if (ServoCD_UseOneCompareMode)
            ServoCD_WriteCompare(ServoCD_INIT_COMPARE_VALUE1);
        #else
            ServoCD_WriteCompare1(ServoCD_INIT_COMPARE_VALUE1);
            ServoCD_WriteCompare2(ServoCD_INIT_COMPARE_VALUE2);
        #endif /* (ServoCD_UseOneCompareMode) */

        #if (ServoCD_KillModeMinTime)
            ServoCD_WriteKillTime(ServoCD_MinimumKillTime);
        #endif /* (ServoCD_KillModeMinTime) */

        #if (ServoCD_DeadBandUsed)
            ServoCD_WriteDeadTime(ServoCD_INIT_DEAD_TIME);
        #endif /* (ServoCD_DeadBandUsed) */

    #if (ServoCD_UseStatus || ServoCD_UsingFixedFunction)
        ServoCD_SetInterruptMode(ServoCD_INIT_INTERRUPTS_MODE);
    #endif /* (ServoCD_UseStatus || ServoCD_UsingFixedFunction) */

    #if (ServoCD_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        ServoCD_GLOBAL_ENABLE |= ServoCD_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        ServoCD_CONTROL2 |= ServoCD_CTRL2_IRQ_SEL;
    #else
        #if(ServoCD_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ServoCD_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            ServoCD_STATUS_AUX_CTRL |= ServoCD_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(ServoCD_interruptState);

            /* Clear the FIFO to enable the ServoCD_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            ServoCD_ClearFIFO();
        #endif /* (ServoCD_UseStatus) */
    #endif /* (ServoCD_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCD_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void ServoCD_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ServoCD_UsingFixedFunction)
        ServoCD_GLOBAL_ENABLE |= ServoCD_BLOCK_EN_MASK;
        ServoCD_GLOBAL_STBY_ENABLE |= ServoCD_BLOCK_STBY_EN_MASK;
    #endif /* (ServoCD_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (ServoCD_UseControl || ServoCD_UsingFixedFunction)
        ServoCD_CONTROL |= ServoCD_CTRL_ENABLE;
    #endif /* (ServoCD_UseControl || ServoCD_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoCD_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void ServoCD_Stop(void) 
{
    #if (ServoCD_UseControl || ServoCD_UsingFixedFunction)
        ServoCD_CONTROL &= ((uint8)(~ServoCD_CTRL_ENABLE));
    #endif /* (ServoCD_UseControl || ServoCD_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (ServoCD_UsingFixedFunction)
        ServoCD_GLOBAL_ENABLE &= ((uint8)(~ServoCD_BLOCK_EN_MASK));
        ServoCD_GLOBAL_STBY_ENABLE &= ((uint8)(~ServoCD_BLOCK_STBY_EN_MASK));
    #endif /* (ServoCD_UsingFixedFunction) */
}

#if (ServoCD_UseOneCompareMode)
    #if (ServoCD_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ServoCD_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ServoCD_SetCompareMode(uint8 comparemode) 
        {
            #if(ServoCD_UsingFixedFunction)

                #if(0 != ServoCD_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << ServoCD_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != ServoCD_CTRL_CMPMODE1_SHIFT) */

                ServoCD_CONTROL3 &= ((uint8)(~ServoCD_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                ServoCD_CONTROL3 |= comparemodemasked;

            #elif (ServoCD_UseControl)

                #if(0 != ServoCD_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << ServoCD_CTRL_CMPMODE1_SHIFT)) &
                                                ServoCD_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & ServoCD_CTRL_CMPMODE1_MASK;
                #endif /* (0 != ServoCD_CTRL_CMPMODE1_SHIFT) */

                #if(0 != ServoCD_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << ServoCD_CTRL_CMPMODE2_SHIFT)) &
                                               ServoCD_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & ServoCD_CTRL_CMPMODE2_MASK;
                #endif /* (0 != ServoCD_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                ServoCD_CONTROL &= ((uint8)(~(ServoCD_CTRL_CMPMODE1_MASK |
                                            ServoCD_CTRL_CMPMODE2_MASK)));
                ServoCD_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (ServoCD_UsingFixedFunction) */
        }
    #endif /* ServoCD_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (ServoCD_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ServoCD_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ServoCD_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != ServoCD_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << ServoCD_CTRL_CMPMODE1_SHIFT)) &
                                           ServoCD_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & ServoCD_CTRL_CMPMODE1_MASK;
            #endif /* (0 != ServoCD_CTRL_CMPMODE1_SHIFT) */

            #if (ServoCD_UseControl)
                ServoCD_CONTROL &= ((uint8)(~ServoCD_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                ServoCD_CONTROL |= comparemodemasked;
            #endif /* (ServoCD_UseControl) */
        }
    #endif /* ServoCD_CompareMode1SW */

#if (ServoCD_CompareMode2SW)


    /*******************************************************************************
    * Function Name: ServoCD_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ServoCD_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != ServoCD_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << ServoCD_CTRL_CMPMODE2_SHIFT)) &
                                                 ServoCD_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & ServoCD_CTRL_CMPMODE2_MASK;
        #endif /* (0 != ServoCD_CTRL_CMPMODE2_SHIFT) */

        #if (ServoCD_UseControl)
            ServoCD_CONTROL &= ((uint8)(~ServoCD_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            ServoCD_CONTROL |= comparemodemasked;
        #endif /* (ServoCD_UseControl) */
    }
    #endif /*ServoCD_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!ServoCD_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ServoCD_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void ServoCD_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(ServoCD_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: ServoCD_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 ServoCD_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(ServoCD_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(ServoCD_CAPTURE_LSB_PTR));
    }

    #if (ServoCD_UseStatus)


        /*******************************************************************************
        * Function Name: ServoCD_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ServoCD_ClearFIFO(void) 
        {
            while(0u != (ServoCD_ReadStatusRegister() & ServoCD_STATUS_FIFONEMPTY))
            {
                (void)ServoCD_ReadCapture();
            }
        }

    #endif /* ServoCD_UseStatus */

#endif /* !ServoCD_UsingFixedFunction */


/*******************************************************************************
* Function Name: ServoCD_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void ServoCD_WritePeriod(uint16 period) 
{
    #if(ServoCD_UsingFixedFunction)
        CY_SET_REG16(ServoCD_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(ServoCD_PERIOD_LSB_PTR, period);
    #endif /* (ServoCD_UsingFixedFunction) */
}

#if (ServoCD_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ServoCD_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void ServoCD_WriteCompare(uint16 compare) \
                                       
    {
        #if(ServoCD_UsingFixedFunction)
            CY_SET_REG16(ServoCD_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(ServoCD_COMPARE1_LSB_PTR, compare);
        #endif /* (ServoCD_UsingFixedFunction) */

        #if (ServoCD_PWMMode == ServoCD__B_PWM__DITHER)
            #if(ServoCD_UsingFixedFunction)
                CY_SET_REG16(ServoCD_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(ServoCD_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (ServoCD_UsingFixedFunction) */
        #endif /* (ServoCD_PWMMode == ServoCD__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: ServoCD_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ServoCD_WriteCompare1(uint16 compare) \
                                        
    {
        #if(ServoCD_UsingFixedFunction)
            CY_SET_REG16(ServoCD_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(ServoCD_COMPARE1_LSB_PTR, compare);
        #endif /* (ServoCD_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: ServoCD_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ServoCD_WriteCompare2(uint16 compare) \
                                        
    {
        #if(ServoCD_UsingFixedFunction)
            CY_SET_REG16(ServoCD_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(ServoCD_COMPARE2_LSB_PTR, compare);
        #endif /* (ServoCD_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (ServoCD_DeadBandUsed)


    /*******************************************************************************
    * Function Name: ServoCD_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ServoCD_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!ServoCD_DeadBand2_4)
            CY_SET_REG8(ServoCD_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            ServoCD_DEADBAND_COUNT &= ((uint8)(~ServoCD_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(ServoCD_DEADBAND_COUNT_SHIFT)
                ServoCD_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << ServoCD_DEADBAND_COUNT_SHIFT)) &
                                                    ServoCD_DEADBAND_COUNT_MASK;
            #else
                ServoCD_DEADBAND_COUNT |= deadtime & ServoCD_DEADBAND_COUNT_MASK;
            #endif /* (ServoCD_DEADBAND_COUNT_SHIFT) */

        #endif /* (!ServoCD_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: ServoCD_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 ServoCD_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!ServoCD_DeadBand2_4)
            return (CY_GET_REG8(ServoCD_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(ServoCD_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(ServoCD_DEADBAND_COUNT & ServoCD_DEADBAND_COUNT_MASK)) >>
                                                                           ServoCD_DEADBAND_COUNT_SHIFT));
            #else
                return (ServoCD_DEADBAND_COUNT & ServoCD_DEADBAND_COUNT_MASK);
            #endif /* (ServoCD_DEADBAND_COUNT_SHIFT) */
        #endif /* (!ServoCD_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (ServoCD_UseStatus || ServoCD_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ServoCD_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ServoCD_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(ServoCD_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: ServoCD_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 ServoCD_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(ServoCD_STATUS_PTR));
    }

#endif /* (ServoCD_UseStatus || ServoCD_UsingFixedFunction) */


#if (ServoCD_UseControl)


    /*******************************************************************************
    * Function Name: ServoCD_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 ServoCD_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(ServoCD_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: ServoCD_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ServoCD_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(ServoCD_CONTROL_PTR, control);
    }

#endif /* (ServoCD_UseControl) */


#if (!ServoCD_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ServoCD_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 ServoCD_ReadCapture(void) 
    {
        return (CY_GET_REG16(ServoCD_CAPTURE_LSB_PTR));
    }

#endif /* (!ServoCD_UsingFixedFunction) */


#if (ServoCD_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ServoCD_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 ServoCD_ReadCompare(void) 
    {
        #if(ServoCD_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(ServoCD_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(ServoCD_COMPARE1_LSB_PTR));
        #endif /* (ServoCD_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: ServoCD_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 ServoCD_ReadCompare1(void) 
    {
        return (CY_GET_REG16(ServoCD_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: ServoCD_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 ServoCD_ReadCompare2(void) 
    {
        return (CY_GET_REG16(ServoCD_COMPARE2_LSB_PTR));
    }

#endif /* (ServoCD_UseOneCompareMode) */


/*******************************************************************************
* Function Name: ServoCD_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 ServoCD_ReadPeriod(void) 
{
    #if(ServoCD_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ServoCD_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(ServoCD_PERIOD_LSB_PTR));
    #endif /* (ServoCD_UsingFixedFunction) */
}

#if ( ServoCD_KillModeMinTime)


    /*******************************************************************************
    * Function Name: ServoCD_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ServoCD_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(ServoCD_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: ServoCD_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 ServoCD_ReadKillTime(void) 
    {
        return (CY_GET_REG8(ServoCD_KILLMODEMINTIME_PTR));
    }

#endif /* ( ServoCD_KillModeMinTime) */

/* [] END OF FILE */
