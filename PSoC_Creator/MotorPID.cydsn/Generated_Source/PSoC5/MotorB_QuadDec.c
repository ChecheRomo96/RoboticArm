/*******************************************************************************
* File Name: MotorB_QuadDec.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#include "MotorB_QuadDec.h"

#if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
    #include "MotorB_QuadDec_PVT.h"
#endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT */

uint8 MotorB_QuadDec_initVar = 0u;


/*******************************************************************************
* Function Name: MotorB_QuadDec_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorB_QuadDec_Init(void) 
{
    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(MotorB_QuadDec_ISR_NUMBER);
        /* Set the ISR to point to the MotorB_QuadDec_isr Interrupt. */
        (void) CyIntSetVector(MotorB_QuadDec_ISR_NUMBER, & MotorB_QuadDec_ISR);
        /* Set the priority. */
        CyIntSetPriority(MotorB_QuadDec_ISR_NUMBER, MotorB_QuadDec_ISR_PRIORITY);
    #endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorB_QuadDec_Enable(void) 
{
    uint8 enableInterrupts;

    MotorB_QuadDec_SetInterruptMask(MotorB_QuadDec_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) MotorB_QuadDec_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    MotorB_QuadDec_SR_AUX_CONTROL |= MotorB_QuadDec_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(MotorB_QuadDec_ISR_NUMBER);
    #endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  MotorB_QuadDec_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MotorB_QuadDec_Start(void) 
{
    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT)
        MotorB_QuadDec_Cnt8_Start();
        MotorB_QuadDec_Cnt8_WriteCounter(MotorB_QuadDec_COUNTER_INIT_VALUE);
    #else
        /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT) || 
        *  (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT) 
        */
        MotorB_QuadDec_Cnt16_Start();
        MotorB_QuadDec_Cnt16_WriteCounter(MotorB_QuadDec_COUNTER_INIT_VALUE);
    #endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT */
    
    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)        
       MotorB_QuadDec_count32SoftPart = 0;
    #endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT */

    if (MotorB_QuadDec_initVar == 0u)
    {
        MotorB_QuadDec_Init();
        MotorB_QuadDec_initVar = 1u;
    }

    MotorB_QuadDec_Enable();
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorB_QuadDec_Stop(void) 
{
    uint8 enableInterrupts;

    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT)
        MotorB_QuadDec_Cnt8_Stop();
    #else 
        /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT) ||
        *  (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
        */
        MotorB_QuadDec_Cnt16_Stop();    /* counter disable */
    #endif /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    MotorB_QuadDec_SR_AUX_CONTROL &= (uint8) (~MotorB_QuadDec_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
        CyIntDisable(MotorB_QuadDec_ISR_NUMBER);    /* interrupt disable */
    #endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  MotorB_QuadDec_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int16 MotorB_QuadDec_GetCounter(void) 
{
    int16 count;
    uint16 tmpCnt;

    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(MotorB_QuadDec_ISR_NUMBER);

        tmpCnt = MotorB_QuadDec_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) MotorB_QuadDec_COUNTER_INIT_VALUE);
        count = MotorB_QuadDec_count32SoftPart + hwCount;

        CyIntEnable(MotorB_QuadDec_ISR_NUMBER);
    #else 
        /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT) || 
        *  (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT)
        */
        #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT)
            tmpCnt = MotorB_QuadDec_Cnt8_ReadCounter();
        #else /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT) */
            tmpCnt = MotorB_QuadDec_Cnt16_ReadCounter();
        #endif  /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT */

        count = (int16) ((int32) tmpCnt -
                (int32) MotorB_QuadDec_COUNTER_INIT_VALUE);

    #endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  MotorB_QuadDec_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MotorB_QuadDec_SetCounter(int16 value) 
{
    #if ((MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT) || \
         (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + MotorB_QuadDec_COUNTER_INIT_VALUE;
        }
        else
        {
            count = MotorB_QuadDec_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT)
            MotorB_QuadDec_Cnt8_WriteCounter(count);
        #else /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT) */
            MotorB_QuadDec_Cnt16_WriteCounter(count);
        #endif  /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT */
    #else /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT) */
        CyIntDisable(MotorB_QuadDec_ISR_NUMBER);

        MotorB_QuadDec_Cnt16_WriteCounter(MotorB_QuadDec_COUNTER_INIT_VALUE);
        MotorB_QuadDec_count32SoftPart = value;

        CyIntEnable(MotorB_QuadDec_ISR_NUMBER);
    #endif  /* (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_8_BIT) ||
             * (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 MotorB_QuadDec_GetEvents(void) 
{
    return (MotorB_QuadDec_STATUS_REG & MotorB_QuadDec_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorB_QuadDec_SetInterruptMask(uint8 mask) 
{
    #if (MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (MotorB_QuadDec_COUNTER_OVERFLOW | MotorB_QuadDec_COUNTER_UNDERFLOW |
                 MotorB_QuadDec_COUNTER_RESET);
    #endif /* MotorB_QuadDec_COUNTER_SIZE == MotorB_QuadDec_COUNTER_SIZE_32_BIT */

    MotorB_QuadDec_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: MotorB_QuadDec_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 MotorB_QuadDec_GetInterruptMask(void) 
{
    return (MotorB_QuadDec_STATUS_MASK & MotorB_QuadDec_INIT_INT_MASK);
}


/* [] END OF FILE */
