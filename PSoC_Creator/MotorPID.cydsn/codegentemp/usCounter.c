/*******************************************************************************
* File Name: usCounter.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 usCounter_initVar = 0u;


/*******************************************************************************
* Function Name: usCounter_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void usCounter_Init(void) 
{
        #if (!usCounter_UsingFixedFunction && !usCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!usCounter_UsingFixedFunction && !usCounter_ControlRegRemoved) */
        
        #if(!usCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 usCounter_interruptState;
        #endif /* (!usCounter_UsingFixedFunction) */
        
        #if (usCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            usCounter_CONTROL &= usCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                usCounter_CONTROL2 &= ((uint8)(~usCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                usCounter_CONTROL3 &= ((uint8)(~usCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (usCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                usCounter_CONTROL |= usCounter_ONESHOT;
            #endif /* (usCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            usCounter_CONTROL2 |= usCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            usCounter_RT1 &= ((uint8)(~usCounter_RT1_MASK));
            usCounter_RT1 |= usCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            usCounter_RT1 &= ((uint8)(~usCounter_SYNCDSI_MASK));
            usCounter_RT1 |= usCounter_SYNCDSI_EN;

        #else
            #if(!usCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = usCounter_CONTROL & ((uint8)(~usCounter_CTRL_CMPMODE_MASK));
            usCounter_CONTROL = ctrl | usCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = usCounter_CONTROL & ((uint8)(~usCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != usCounter_CAPTURE_MODE_CONF)
                usCounter_CONTROL = ctrl | usCounter_DEFAULT_CAPTURE_MODE;
            #else
                usCounter_CONTROL = ctrl;
            #endif /* 0 != usCounter_CAPTURE_MODE */ 
            
            #endif /* (!usCounter_ControlRegRemoved) */
        #endif /* (usCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!usCounter_UsingFixedFunction)
            usCounter_ClearFIFO();
        #endif /* (!usCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        usCounter_WritePeriod(usCounter_INIT_PERIOD_VALUE);
        #if (!(usCounter_UsingFixedFunction && (CY_PSOC5A)))
            usCounter_WriteCounter(usCounter_INIT_COUNTER_VALUE);
        #endif /* (!(usCounter_UsingFixedFunction && (CY_PSOC5A))) */
        usCounter_SetInterruptMode(usCounter_INIT_INTERRUPTS_MASK);
        
        #if (!usCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)usCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            usCounter_WriteCompare(usCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            usCounter_interruptState = CyEnterCriticalSection();
            
            usCounter_STATUS_AUX_CTRL |= usCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(usCounter_interruptState);
            
        #endif /* (!usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void usCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (usCounter_UsingFixedFunction)
        usCounter_GLOBAL_ENABLE |= usCounter_BLOCK_EN_MASK;
        usCounter_GLOBAL_STBY_ENABLE |= usCounter_BLOCK_STBY_EN_MASK;
    #endif /* (usCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!usCounter_ControlRegRemoved || usCounter_UsingFixedFunction)
        usCounter_CONTROL |= usCounter_CTRL_ENABLE;                
    #endif /* (!usCounter_ControlRegRemoved || usCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: usCounter_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  usCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void usCounter_Start(void) 
{
    if(usCounter_initVar == 0u)
    {
        usCounter_Init();
        
        usCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    usCounter_Enable();        
}


/*******************************************************************************
* Function Name: usCounter_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void usCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!usCounter_ControlRegRemoved || usCounter_UsingFixedFunction)
        usCounter_CONTROL &= ((uint8)(~usCounter_CTRL_ENABLE));        
    #endif /* (!usCounter_ControlRegRemoved || usCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (usCounter_UsingFixedFunction)
        usCounter_GLOBAL_ENABLE &= ((uint8)(~usCounter_BLOCK_EN_MASK));
        usCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~usCounter_BLOCK_STBY_EN_MASK));
    #endif /* (usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void usCounter_SetInterruptMode(uint8 interruptsMask) 
{
    usCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: usCounter_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   usCounter_ReadStatusRegister(void) 
{
    return usCounter_STATUS;
}


#if(!usCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: usCounter_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   usCounter_ReadControlRegister(void) 
{
    return usCounter_CONTROL;
}


/*******************************************************************************
* Function Name: usCounter_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    usCounter_WriteControlRegister(uint8 control) 
{
    usCounter_CONTROL = control;
}

#endif  /* (!usCounter_ControlRegRemoved) */


#if (!(usCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: usCounter_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void usCounter_WriteCounter(uint8 counter) \
                                   
{
    #if(usCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (usCounter_GLOBAL_ENABLE & usCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        usCounter_GLOBAL_ENABLE |= usCounter_BLOCK_EN_MASK;
        CY_SET_REG16(usCounter_COUNTER_LSB_PTR, (uint16)counter);
        usCounter_GLOBAL_ENABLE &= ((uint8)(~usCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(usCounter_COUNTER_LSB_PTR, counter);
    #endif /* (usCounter_UsingFixedFunction) */
}
#endif /* (!(usCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: usCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 usCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(usCounter_UsingFixedFunction)
		(void)CY_GET_REG16(usCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(usCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (usCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(usCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(usCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(usCounter_STATICCOUNT_LSB_PTR));
    #endif /* (usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 usCounter_ReadCapture(void) 
{
    #if(usCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(usCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(usCounter_STATICCOUNT_LSB_PTR));
    #endif /* (usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void usCounter_WritePeriod(uint8 period) 
{
    #if(usCounter_UsingFixedFunction)
        CY_SET_REG16(usCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(usCounter_PERIOD_LSB_PTR, period);
    #endif /* (usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 usCounter_ReadPeriod(void) 
{
    #if(usCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(usCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(usCounter_PERIOD_LSB_PTR));
    #endif /* (usCounter_UsingFixedFunction) */
}


#if (!usCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: usCounter_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void usCounter_WriteCompare(uint8 compare) \
                                   
{
    #if(usCounter_UsingFixedFunction)
        CY_SET_REG16(usCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(usCounter_COMPARE_LSB_PTR, compare);
    #endif /* (usCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: usCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 usCounter_ReadCompare(void) 
{
    return (CY_GET_REG8(usCounter_COMPARE_LSB_PTR));
}


#if (usCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: usCounter_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void usCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    usCounter_CONTROL &= ((uint8)(~usCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    usCounter_CONTROL |= compareMode;
}
#endif  /* (usCounter_COMPARE_MODE_SOFTWARE) */


#if (usCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: usCounter_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void usCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    usCounter_CONTROL &= ((uint8)(~usCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    usCounter_CONTROL |= ((uint8)((uint8)captureMode << usCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (usCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: usCounter_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void usCounter_ClearFIFO(void) 
{

    while(0u != (usCounter_ReadStatusRegister() & usCounter_STATUS_FIFONEMP))
    {
        (void)usCounter_ReadCapture();
    }

}
#endif  /* (!usCounter_UsingFixedFunction) */


/* [] END OF FILE */

