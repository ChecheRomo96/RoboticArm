/*******************************************************************************
* File Name: usCounter.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_usCounter_H)
#define CY_COUNTER_usCounter_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 usCounter_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed usCounter_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef usCounter_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* usCounter_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define usCounter_Resolution            8u
#define usCounter_UsingFixedFunction    1u
#define usCounter_ControlRegRemoved     0u
#define usCounter_COMPARE_MODE_SOFTWARE 0u
#define usCounter_CAPTURE_MODE_SOFTWARE 0u
#define usCounter_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint8 CounterUdb;         /* Current Counter Value */

    #if (!usCounter_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!usCounter_ControlRegRemoved) */

}usCounter_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    usCounter_Start(void) ;
void    usCounter_Stop(void) ;
void    usCounter_SetInterruptMode(uint8 interruptsMask) ;
uint8   usCounter_ReadStatusRegister(void) ;
#define usCounter_GetInterruptSource() usCounter_ReadStatusRegister()
#if(!usCounter_ControlRegRemoved)
    uint8   usCounter_ReadControlRegister(void) ;
    void    usCounter_WriteControlRegister(uint8 control) \
        ;
#endif /* (!usCounter_ControlRegRemoved) */
#if (!(usCounter_UsingFixedFunction && (CY_PSOC5A)))
    void    usCounter_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(usCounter_UsingFixedFunction && (CY_PSOC5A))) */
uint8  usCounter_ReadCounter(void) ;
uint8  usCounter_ReadCapture(void) ;
void    usCounter_WritePeriod(uint8 period) \
    ;
uint8  usCounter_ReadPeriod( void ) ;
#if (!usCounter_UsingFixedFunction)
    void    usCounter_WriteCompare(uint8 compare) \
        ;
    uint8  usCounter_ReadCompare( void ) \
        ;
#endif /* (!usCounter_UsingFixedFunction) */

#if (usCounter_COMPARE_MODE_SOFTWARE)
    void    usCounter_SetCompareMode(uint8 compareMode) ;
#endif /* (usCounter_COMPARE_MODE_SOFTWARE) */
#if (usCounter_CAPTURE_MODE_SOFTWARE)
    void    usCounter_SetCaptureMode(uint8 captureMode) ;
#endif /* (usCounter_CAPTURE_MODE_SOFTWARE) */
void usCounter_ClearFIFO(void)     ;
void usCounter_Init(void)          ;
void usCounter_Enable(void)        ;
void usCounter_SaveConfig(void)    ;
void usCounter_RestoreConfig(void) ;
void usCounter_Sleep(void)         ;
void usCounter_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define usCounter__B_COUNTER__LESS_THAN 1
#define usCounter__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define usCounter__B_COUNTER__EQUAL 0
#define usCounter__B_COUNTER__GREATER_THAN 3
#define usCounter__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define usCounter__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define usCounter_CMP_MODE_LT 1u
#define usCounter_CMP_MODE_LTE 2u
#define usCounter_CMP_MODE_EQ 0u
#define usCounter_CMP_MODE_GT 3u
#define usCounter_CMP_MODE_GTE 4u
#define usCounter_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define usCounter__B_COUNTER__NONE 0
#define usCounter__B_COUNTER__RISING_EDGE 1
#define usCounter__B_COUNTER__FALLING_EDGE 2
#define usCounter__B_COUNTER__EITHER_EDGE 3
#define usCounter__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define usCounter_CAP_MODE_NONE 0u
#define usCounter_CAP_MODE_RISE 1u
#define usCounter_CAP_MODE_FALL 2u
#define usCounter_CAP_MODE_BOTH 3u
#define usCounter_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define usCounter_CAPTURE_MODE_CONF       0u
#define usCounter_INIT_PERIOD_VALUE       255u
#define usCounter_INIT_COUNTER_VALUE      0u
#if (usCounter_UsingFixedFunction)
#define usCounter_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << usCounter_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define usCounter_INIT_COMPARE_VALUE      128u
#define usCounter_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << usCounter_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << usCounter_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << usCounter_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << usCounter_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << usCounter_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define usCounter_DEFAULT_COMPARE_MODE    1u

#if( 0 != usCounter_CAPTURE_MODE_CONF)
    #define usCounter_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << usCounter_CTRL_CAPMODE0_SHIFT))
#else    
    #define usCounter_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != usCounter_CAPTURE_MODE_CONF) */

#endif /* (usCounter_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (usCounter_UsingFixedFunction)
    #define usCounter_STATICCOUNT_LSB     (*(reg16 *) usCounter_CounterHW__CAP0 )
    #define usCounter_STATICCOUNT_LSB_PTR ( (reg16 *) usCounter_CounterHW__CAP0 )
    #define usCounter_PERIOD_LSB          (*(reg16 *) usCounter_CounterHW__PER0 )
    #define usCounter_PERIOD_LSB_PTR      ( (reg16 *) usCounter_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define usCounter_COMPARE_LSB         (*(reg16 *) usCounter_CounterHW__CNT_CMP0 )
    #define usCounter_COMPARE_LSB_PTR     ( (reg16 *) usCounter_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define usCounter_COUNTER_LSB         (*(reg16 *) usCounter_CounterHW__CNT_CMP0 )
    #define usCounter_COUNTER_LSB_PTR     ( (reg16 *) usCounter_CounterHW__CNT_CMP0 )
    #define usCounter_RT1                 (*(reg8 *) usCounter_CounterHW__RT1)
    #define usCounter_RT1_PTR             ( (reg8 *) usCounter_CounterHW__RT1)
#else
    
    #if (usCounter_Resolution <= 8u) /* 8-bit Counter */
    
        #define usCounter_STATICCOUNT_LSB     (*(reg8 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define usCounter_STATICCOUNT_LSB_PTR ( (reg8 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define usCounter_PERIOD_LSB          (*(reg8 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define usCounter_PERIOD_LSB_PTR      ( (reg8 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define usCounter_COMPARE_LSB         (*(reg8 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define usCounter_COMPARE_LSB_PTR     ( (reg8 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define usCounter_COUNTER_LSB         (*(reg8 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define usCounter_COUNTER_LSB_PTR     ( (reg8 *)\
            usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(usCounter_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define usCounter_STATICCOUNT_LSB     (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define usCounter_STATICCOUNT_LSB_PTR ( (reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define usCounter_PERIOD_LSB          (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define usCounter_PERIOD_LSB_PTR      ( (reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define usCounter_COMPARE_LSB         (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define usCounter_COMPARE_LSB_PTR     ( (reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define usCounter_COUNTER_LSB         (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define usCounter_COUNTER_LSB_PTR     ( (reg16 *)\
                usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define usCounter_STATICCOUNT_LSB     (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define usCounter_STATICCOUNT_LSB_PTR ( (reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define usCounter_PERIOD_LSB          (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define usCounter_PERIOD_LSB_PTR      ( (reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define usCounter_COMPARE_LSB         (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define usCounter_COMPARE_LSB_PTR     ( (reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define usCounter_COUNTER_LSB         (*(reg16 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define usCounter_COUNTER_LSB_PTR     ( (reg16 *)\
                usCounter_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(usCounter_Resolution <= 24u) /* 24-bit Counter */
        
        #define usCounter_STATICCOUNT_LSB     (*(reg32 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define usCounter_STATICCOUNT_LSB_PTR ( (reg32 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define usCounter_PERIOD_LSB          (*(reg32 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define usCounter_PERIOD_LSB_PTR      ( (reg32 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define usCounter_COMPARE_LSB         (*(reg32 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define usCounter_COMPARE_LSB_PTR     ( (reg32 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define usCounter_COUNTER_LSB         (*(reg32 *) \
            usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define usCounter_COUNTER_LSB_PTR     ( (reg32 *)\
            usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define usCounter_STATICCOUNT_LSB     (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define usCounter_STATICCOUNT_LSB_PTR ( (reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define usCounter_PERIOD_LSB          (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define usCounter_PERIOD_LSB_PTR      ( (reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define usCounter_COMPARE_LSB         (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define usCounter_COMPARE_LSB_PTR     ( (reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define usCounter_COUNTER_LSB         (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define usCounter_COUNTER_LSB_PTR     ( (reg32 *)\
                usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define usCounter_STATICCOUNT_LSB     (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define usCounter_STATICCOUNT_LSB_PTR ( (reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define usCounter_PERIOD_LSB          (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define usCounter_PERIOD_LSB_PTR      ( (reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define usCounter_COMPARE_LSB         (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define usCounter_COMPARE_LSB_PTR     ( (reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define usCounter_COUNTER_LSB         (*(reg32 *) \
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define usCounter_COUNTER_LSB_PTR     ( (reg32 *)\
                usCounter_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define usCounter_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                usCounter_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define usCounter_AUX_CONTROLDP0 \
        (*(reg8 *) usCounter_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define usCounter_AUX_CONTROLDP0_PTR \
        ( (reg8 *) usCounter_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (usCounter_Resolution == 16 || usCounter_Resolution == 24 || usCounter_Resolution == 32)
       #define usCounter_AUX_CONTROLDP1 \
           (*(reg8 *) usCounter_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define usCounter_AUX_CONTROLDP1_PTR \
           ( (reg8 *) usCounter_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (usCounter_Resolution == 16 || usCounter_Resolution == 24 || usCounter_Resolution == 32) */
    
    #if (usCounter_Resolution == 24 || usCounter_Resolution == 32)
       #define usCounter_AUX_CONTROLDP2 \
           (*(reg8 *) usCounter_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define usCounter_AUX_CONTROLDP2_PTR \
           ( (reg8 *) usCounter_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (usCounter_Resolution == 24 || usCounter_Resolution == 32) */
    
    #if (usCounter_Resolution == 32)
       #define usCounter_AUX_CONTROLDP3 \
           (*(reg8 *) usCounter_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define usCounter_AUX_CONTROLDP3_PTR \
           ( (reg8 *) usCounter_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (usCounter_Resolution == 32) */

#endif  /* (usCounter_UsingFixedFunction) */

#if (usCounter_UsingFixedFunction)
    #define usCounter_STATUS         (*(reg8 *) usCounter_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define usCounter_STATUS_MASK             (*(reg8 *) usCounter_CounterHW__SR0 )
    #define usCounter_STATUS_MASK_PTR         ( (reg8 *) usCounter_CounterHW__SR0 )
    #define usCounter_CONTROL                 (*(reg8 *) usCounter_CounterHW__CFG0)
    #define usCounter_CONTROL_PTR             ( (reg8 *) usCounter_CounterHW__CFG0)
    #define usCounter_CONTROL2                (*(reg8 *) usCounter_CounterHW__CFG1)
    #define usCounter_CONTROL2_PTR            ( (reg8 *) usCounter_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define usCounter_CONTROL3       (*(reg8 *) usCounter_CounterHW__CFG2)
        #define usCounter_CONTROL3_PTR   ( (reg8 *) usCounter_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define usCounter_GLOBAL_ENABLE           (*(reg8 *) usCounter_CounterHW__PM_ACT_CFG)
    #define usCounter_GLOBAL_ENABLE_PTR       ( (reg8 *) usCounter_CounterHW__PM_ACT_CFG)
    #define usCounter_GLOBAL_STBY_ENABLE      (*(reg8 *) usCounter_CounterHW__PM_STBY_CFG)
    #define usCounter_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) usCounter_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define usCounter_BLOCK_EN_MASK          usCounter_CounterHW__PM_ACT_MSK
    #define usCounter_BLOCK_STBY_EN_MASK     usCounter_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define usCounter_CTRL_ENABLE_SHIFT      0x00u
    #define usCounter_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define usCounter_CTRL_ENABLE            ((uint8)((uint8)0x01u << usCounter_CTRL_ENABLE_SHIFT))         
    #define usCounter_ONESHOT                ((uint8)((uint8)0x01u << usCounter_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define usCounter_CTRL_MODE_SHIFT        0x01u    
        #define usCounter_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << usCounter_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define usCounter_CTRL_MODE_SHIFT        0x00u    
        #define usCounter_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << usCounter_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define usCounter_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define usCounter_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << usCounter_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define usCounter_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define usCounter_STATUS_ZERO_INT_EN_MASK_SHIFT      (usCounter_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define usCounter_STATUS_ZERO            ((uint8)((uint8)0x01u << usCounter_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define usCounter_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)usCounter_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define usCounter_RT1_SHIFT            0x04u
    #define usCounter_RT1_MASK             ((uint8)((uint8)0x03u << usCounter_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define usCounter_SYNC                 ((uint8)((uint8)0x03u << usCounter_RT1_SHIFT))
    #define usCounter_SYNCDSI_SHIFT        0x00u
    #define usCounter_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << usCounter_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define usCounter_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << usCounter_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !usCounter_UsingFixedFunction */
    #define usCounter_STATUS               (* (reg8 *) usCounter_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define usCounter_STATUS_PTR           (  (reg8 *) usCounter_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define usCounter_STATUS_MASK          (* (reg8 *) usCounter_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define usCounter_STATUS_MASK_PTR      (  (reg8 *) usCounter_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define usCounter_STATUS_AUX_CTRL      (*(reg8 *) usCounter_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define usCounter_STATUS_AUX_CTRL_PTR  ( (reg8 *) usCounter_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define usCounter_CONTROL              (* (reg8 *) usCounter_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define usCounter_CONTROL_PTR          (  (reg8 *) usCounter_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define usCounter_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define usCounter_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define usCounter_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define usCounter_CTRL_CMPMODE_MASK      0x07u 
    #define usCounter_CTRL_CAPMODE_MASK      0x03u  
    #define usCounter_CTRL_RESET             ((uint8)((uint8)0x01u << usCounter_CTRL_RESET_SHIFT))  
    #define usCounter_CTRL_ENABLE            ((uint8)((uint8)0x01u << usCounter_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define usCounter_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define usCounter_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define usCounter_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define usCounter_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define usCounter_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define usCounter_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define usCounter_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define usCounter_STATUS_CMP_INT_EN_MASK_SHIFT       usCounter_STATUS_CMP_SHIFT       
    #define usCounter_STATUS_ZERO_INT_EN_MASK_SHIFT      usCounter_STATUS_ZERO_SHIFT      
    #define usCounter_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  usCounter_STATUS_OVERFLOW_SHIFT  
    #define usCounter_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT usCounter_STATUS_UNDERFLOW_SHIFT 
    #define usCounter_STATUS_CAPTURE_INT_EN_MASK_SHIFT   usCounter_STATUS_CAPTURE_SHIFT   
    #define usCounter_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  usCounter_STATUS_FIFOFULL_SHIFT  
    #define usCounter_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  usCounter_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define usCounter_STATUS_CMP             ((uint8)((uint8)0x01u << usCounter_STATUS_CMP_SHIFT))  
    #define usCounter_STATUS_ZERO            ((uint8)((uint8)0x01u << usCounter_STATUS_ZERO_SHIFT)) 
    #define usCounter_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << usCounter_STATUS_OVERFLOW_SHIFT)) 
    #define usCounter_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << usCounter_STATUS_UNDERFLOW_SHIFT)) 
    #define usCounter_STATUS_CAPTURE         ((uint8)((uint8)0x01u << usCounter_STATUS_CAPTURE_SHIFT)) 
    #define usCounter_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << usCounter_STATUS_FIFOFULL_SHIFT))
    #define usCounter_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << usCounter_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define usCounter_STATUS_CMP_INT_EN_MASK            usCounter_STATUS_CMP                    
    #define usCounter_STATUS_ZERO_INT_EN_MASK           usCounter_STATUS_ZERO            
    #define usCounter_STATUS_OVERFLOW_INT_EN_MASK       usCounter_STATUS_OVERFLOW        
    #define usCounter_STATUS_UNDERFLOW_INT_EN_MASK      usCounter_STATUS_UNDERFLOW       
    #define usCounter_STATUS_CAPTURE_INT_EN_MASK        usCounter_STATUS_CAPTURE         
    #define usCounter_STATUS_FIFOFULL_INT_EN_MASK       usCounter_STATUS_FIFOFULL        
    #define usCounter_STATUS_FIFONEMP_INT_EN_MASK       usCounter_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define usCounter_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define usCounter_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define usCounter_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define usCounter_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define usCounter_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define usCounter_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* usCounter_UsingFixedFunction */

#endif  /* CY_COUNTER_usCounter_H */


/* [] END OF FILE */

