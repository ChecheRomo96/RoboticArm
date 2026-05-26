/*******************************************************************************
* File Name: ServoCD.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_ServoCD_H)
#define CY_PWM_ServoCD_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ServoCD_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define ServoCD_Resolution                     (16u)
#define ServoCD_UsingFixedFunction             (0u)
#define ServoCD_DeadBandMode                   (0u)
#define ServoCD_KillModeMinTime                (0u)
#define ServoCD_KillMode                       (0u)
#define ServoCD_PWMMode                        (1u)
#define ServoCD_PWMModeIsCenterAligned         (0u)
#define ServoCD_DeadBandUsed                   (0u)
#define ServoCD_DeadBand2_4                    (0u)

#if !defined(ServoCD_PWMUDB_genblk8_stsreg__REMOVED)
    #define ServoCD_UseStatus                  (1u)
#else
    #define ServoCD_UseStatus                  (0u)
#endif /* !defined(ServoCD_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(ServoCD_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define ServoCD_UseControl                 (1u)
#else
    #define ServoCD_UseControl                 (0u)
#endif /* !defined(ServoCD_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define ServoCD_UseOneCompareMode              (0u)
#define ServoCD_MinimumKillTime                (1u)
#define ServoCD_EnableMode                     (0u)

#define ServoCD_CompareMode1SW                 (0u)
#define ServoCD_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define ServoCD__B_PWM__DISABLED 0
#define ServoCD__B_PWM__ASYNCHRONOUS 1
#define ServoCD__B_PWM__SINGLECYCLE 2
#define ServoCD__B_PWM__LATCHED 3
#define ServoCD__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define ServoCD__B_PWM__DBMDISABLED 0
#define ServoCD__B_PWM__DBM_2_4_CLOCKS 1
#define ServoCD__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define ServoCD__B_PWM__ONE_OUTPUT 0
#define ServoCD__B_PWM__TWO_OUTPUTS 1
#define ServoCD__B_PWM__DUAL_EDGE 2
#define ServoCD__B_PWM__CENTER_ALIGN 3
#define ServoCD__B_PWM__DITHER 5
#define ServoCD__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define ServoCD__B_PWM__LESS_THAN 1
#define ServoCD__B_PWM__LESS_THAN_OR_EQUAL 2
#define ServoCD__B_PWM__GREATER_THAN 3
#define ServoCD__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define ServoCD__B_PWM__EQUAL 0
#define ServoCD__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!ServoCD_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!ServoCD_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!ServoCD_PWMModeIsCenterAligned) */
        #if (ServoCD_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (ServoCD_UseStatus) */

        /* Backup for Deadband parameters */
        #if(ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_256_CLOCKS || \
            ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(ServoCD_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (ServoCD_KillModeMinTime) */

        /* Backup control register */
        #if(ServoCD_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (ServoCD_UseControl) */

    #endif /* (!ServoCD_UsingFixedFunction) */

}ServoCD_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    ServoCD_Start(void) ;
void    ServoCD_Stop(void) ;

#if (ServoCD_UseStatus || ServoCD_UsingFixedFunction)
    void  ServoCD_SetInterruptMode(uint8 interruptMode) ;
    uint8 ServoCD_ReadStatusRegister(void) ;
#endif /* (ServoCD_UseStatus || ServoCD_UsingFixedFunction) */

#define ServoCD_GetInterruptSource() ServoCD_ReadStatusRegister()

#if (ServoCD_UseControl)
    uint8 ServoCD_ReadControlRegister(void) ;
    void  ServoCD_WriteControlRegister(uint8 control)
          ;
#endif /* (ServoCD_UseControl) */

#if (ServoCD_UseOneCompareMode)
   #if (ServoCD_CompareMode1SW)
       void    ServoCD_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (ServoCD_CompareMode1SW) */
#else
    #if (ServoCD_CompareMode1SW)
        void    ServoCD_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (ServoCD_CompareMode1SW) */
    #if (ServoCD_CompareMode2SW)
        void    ServoCD_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (ServoCD_CompareMode2SW) */
#endif /* (ServoCD_UseOneCompareMode) */

#if (!ServoCD_UsingFixedFunction)
    uint16   ServoCD_ReadCounter(void) ;
    uint16 ServoCD_ReadCapture(void) ;

    #if (ServoCD_UseStatus)
            void ServoCD_ClearFIFO(void) ;
    #endif /* (ServoCD_UseStatus) */

    void    ServoCD_WriteCounter(uint16 counter)
            ;
#endif /* (!ServoCD_UsingFixedFunction) */

void    ServoCD_WritePeriod(uint16 period)
        ;
uint16 ServoCD_ReadPeriod(void) ;

#if (ServoCD_UseOneCompareMode)
    void    ServoCD_WriteCompare(uint16 compare)
            ;
    uint16 ServoCD_ReadCompare(void) ;
#else
    void    ServoCD_WriteCompare1(uint16 compare)
            ;
    uint16 ServoCD_ReadCompare1(void) ;
    void    ServoCD_WriteCompare2(uint16 compare)
            ;
    uint16 ServoCD_ReadCompare2(void) ;
#endif /* (ServoCD_UseOneCompareMode) */


#if (ServoCD_DeadBandUsed)
    void    ServoCD_WriteDeadTime(uint8 deadtime) ;
    uint8   ServoCD_ReadDeadTime(void) ;
#endif /* (ServoCD_DeadBandUsed) */

#if ( ServoCD_KillModeMinTime)
    void ServoCD_WriteKillTime(uint8 killtime) ;
    uint8 ServoCD_ReadKillTime(void) ;
#endif /* ( ServoCD_KillModeMinTime) */

void ServoCD_Init(void) ;
void ServoCD_Enable(void) ;
void ServoCD_Sleep(void) ;
void ServoCD_Wakeup(void) ;
void ServoCD_SaveConfig(void) ;
void ServoCD_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define ServoCD_INIT_PERIOD_VALUE          (24000u)
#define ServoCD_INIT_COMPARE_VALUE1        (0u)
#define ServoCD_INIT_COMPARE_VALUE2        (0u)
#define ServoCD_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    ServoCD_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ServoCD_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ServoCD_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ServoCD_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define ServoCD_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  ServoCD_CTRL_CMPMODE2_SHIFT)
#define ServoCD_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  ServoCD_CTRL_CMPMODE1_SHIFT)
#define ServoCD_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (ServoCD_UsingFixedFunction)
   #define ServoCD_PERIOD_LSB              (*(reg16 *) ServoCD_PWMHW__PER0)
   #define ServoCD_PERIOD_LSB_PTR          ( (reg16 *) ServoCD_PWMHW__PER0)
   #define ServoCD_COMPARE1_LSB            (*(reg16 *) ServoCD_PWMHW__CNT_CMP0)
   #define ServoCD_COMPARE1_LSB_PTR        ( (reg16 *) ServoCD_PWMHW__CNT_CMP0)
   #define ServoCD_COMPARE2_LSB            (0x00u)
   #define ServoCD_COMPARE2_LSB_PTR        (0x00u)
   #define ServoCD_COUNTER_LSB             (*(reg16 *) ServoCD_PWMHW__CNT_CMP0)
   #define ServoCD_COUNTER_LSB_PTR         ( (reg16 *) ServoCD_PWMHW__CNT_CMP0)
   #define ServoCD_CAPTURE_LSB             (*(reg16 *) ServoCD_PWMHW__CAP0)
   #define ServoCD_CAPTURE_LSB_PTR         ( (reg16 *) ServoCD_PWMHW__CAP0)
   #define ServoCD_RT1                     (*(reg8 *)  ServoCD_PWMHW__RT1)
   #define ServoCD_RT1_PTR                 ( (reg8 *)  ServoCD_PWMHW__RT1)

#else
   #if (ServoCD_Resolution == 8u) /* 8bit - PWM */

       #if(ServoCD_PWMModeIsCenterAligned)
           #define ServoCD_PERIOD_LSB      (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define ServoCD_PERIOD_LSB_PTR  ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define ServoCD_PERIOD_LSB      (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define ServoCD_PERIOD_LSB_PTR  ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (ServoCD_PWMModeIsCenterAligned) */

       #define ServoCD_COMPARE1_LSB        (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define ServoCD_COMPARE1_LSB_PTR    ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define ServoCD_COMPARE2_LSB        (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define ServoCD_COMPARE2_LSB_PTR    ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define ServoCD_COUNTERCAP_LSB      (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define ServoCD_COUNTERCAP_LSB_PTR  ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define ServoCD_COUNTER_LSB         (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define ServoCD_COUNTER_LSB_PTR     ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define ServoCD_CAPTURE_LSB         (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define ServoCD_CAPTURE_LSB_PTR     ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(ServoCD_PWMModeIsCenterAligned)
               #define ServoCD_PERIOD_LSB      (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define ServoCD_PERIOD_LSB_PTR  ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define ServoCD_PERIOD_LSB      (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define ServoCD_PERIOD_LSB_PTR  ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (ServoCD_PWMModeIsCenterAligned) */

            #define ServoCD_COMPARE1_LSB       (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define ServoCD_COMPARE1_LSB_PTR   ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define ServoCD_COMPARE2_LSB       (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define ServoCD_COMPARE2_LSB_PTR   ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define ServoCD_COUNTERCAP_LSB     (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define ServoCD_COUNTERCAP_LSB_PTR ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define ServoCD_COUNTER_LSB        (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define ServoCD_COUNTER_LSB_PTR    ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define ServoCD_CAPTURE_LSB        (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define ServoCD_CAPTURE_LSB_PTR    ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(ServoCD_PWMModeIsCenterAligned)
               #define ServoCD_PERIOD_LSB      (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define ServoCD_PERIOD_LSB_PTR  ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define ServoCD_PERIOD_LSB      (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define ServoCD_PERIOD_LSB_PTR  ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (ServoCD_PWMModeIsCenterAligned) */

            #define ServoCD_COMPARE1_LSB       (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define ServoCD_COMPARE1_LSB_PTR   ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define ServoCD_COMPARE2_LSB       (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define ServoCD_COMPARE2_LSB_PTR   ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define ServoCD_COUNTERCAP_LSB     (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define ServoCD_COUNTERCAP_LSB_PTR ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define ServoCD_COUNTER_LSB        (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define ServoCD_COUNTER_LSB_PTR    ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define ServoCD_CAPTURE_LSB        (*(reg16 *) ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define ServoCD_CAPTURE_LSB_PTR    ((reg16 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define ServoCD_AUX_CONTROLDP1          (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define ServoCD_AUX_CONTROLDP1_PTR      ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (ServoCD_Resolution == 8) */

   #define ServoCD_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define ServoCD_AUX_CONTROLDP0          (*(reg8 *)  ServoCD_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define ServoCD_AUX_CONTROLDP0_PTR      ((reg8 *)   ServoCD_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (ServoCD_UsingFixedFunction) */

#if(ServoCD_KillModeMinTime )
    #define ServoCD_KILLMODEMINTIME        (*(reg8 *)  ServoCD_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define ServoCD_KILLMODEMINTIME_PTR    ((reg8 *)   ServoCD_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (ServoCD_KillModeMinTime ) */

#if(ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_256_CLOCKS)
    #define ServoCD_DEADBAND_COUNT         (*(reg8 *)  ServoCD_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ServoCD_DEADBAND_COUNT_PTR     ((reg8 *)   ServoCD_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ServoCD_DEADBAND_LSB_PTR       ((reg8 *)   ServoCD_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define ServoCD_DEADBAND_LSB           (*(reg8 *)  ServoCD_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (ServoCD_UsingFixedFunction)
        #define ServoCD_DEADBAND_COUNT         (*(reg8 *)  ServoCD_PWMHW__CFG0)
        #define ServoCD_DEADBAND_COUNT_PTR     ((reg8 *)   ServoCD_PWMHW__CFG0)
        #define ServoCD_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ServoCD_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define ServoCD_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define ServoCD_DEADBAND_COUNT         (*(reg8 *)  ServoCD_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ServoCD_DEADBAND_COUNT_PTR     ((reg8 *)   ServoCD_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ServoCD_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ServoCD_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define ServoCD_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (ServoCD_UsingFixedFunction) */
#endif /* (ServoCD_DeadBandMode == ServoCD__B_PWM__DBM_256_CLOCKS) */



#if (ServoCD_UsingFixedFunction)
    #define ServoCD_STATUS                 (*(reg8 *) ServoCD_PWMHW__SR0)
    #define ServoCD_STATUS_PTR             ((reg8 *) ServoCD_PWMHW__SR0)
    #define ServoCD_STATUS_MASK            (*(reg8 *) ServoCD_PWMHW__SR0)
    #define ServoCD_STATUS_MASK_PTR        ((reg8 *) ServoCD_PWMHW__SR0)
    #define ServoCD_CONTROL                (*(reg8 *) ServoCD_PWMHW__CFG0)
    #define ServoCD_CONTROL_PTR            ((reg8 *) ServoCD_PWMHW__CFG0)
    #define ServoCD_CONTROL2               (*(reg8 *) ServoCD_PWMHW__CFG1)
    #define ServoCD_CONTROL3               (*(reg8 *) ServoCD_PWMHW__CFG2)
    #define ServoCD_GLOBAL_ENABLE          (*(reg8 *) ServoCD_PWMHW__PM_ACT_CFG)
    #define ServoCD_GLOBAL_ENABLE_PTR      ( (reg8 *) ServoCD_PWMHW__PM_ACT_CFG)
    #define ServoCD_GLOBAL_STBY_ENABLE     (*(reg8 *) ServoCD_PWMHW__PM_STBY_CFG)
    #define ServoCD_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) ServoCD_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define ServoCD_BLOCK_EN_MASK          (ServoCD_PWMHW__PM_ACT_MSK)
    #define ServoCD_BLOCK_STBY_EN_MASK     (ServoCD_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define ServoCD_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define ServoCD_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define ServoCD_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define ServoCD_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define ServoCD_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define ServoCD_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define ServoCD_CTRL_ENABLE            (uint8)((uint8)0x01u << ServoCD_CTRL_ENABLE_SHIFT)
    #define ServoCD_CTRL_RESET             (uint8)((uint8)0x01u << ServoCD_CTRL_RESET_SHIFT)
    #define ServoCD_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ServoCD_CTRL_CMPMODE2_SHIFT)
    #define ServoCD_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ServoCD_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ServoCD_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define ServoCD_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << ServoCD_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define ServoCD_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define ServoCD_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define ServoCD_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define ServoCD_STATUS_TC_INT_EN_MASK_SHIFT            (ServoCD_STATUS_TC_SHIFT - 4u)
    #define ServoCD_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define ServoCD_STATUS_CMP1_INT_EN_MASK_SHIFT          (ServoCD_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define ServoCD_STATUS_TC              (uint8)((uint8)0x01u << ServoCD_STATUS_TC_SHIFT)
    #define ServoCD_STATUS_CMP1            (uint8)((uint8)0x01u << ServoCD_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define ServoCD_STATUS_TC_INT_EN_MASK              (uint8)((uint8)ServoCD_STATUS_TC >> 4u)
    #define ServoCD_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)ServoCD_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define ServoCD_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define ServoCD_RT1_MASK              (uint8)((uint8)0x03u << ServoCD_RT1_SHIFT)
    #define ServoCD_SYNC                  (uint8)((uint8)0x03u << ServoCD_RT1_SHIFT)
    #define ServoCD_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define ServoCD_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << ServoCD_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define ServoCD_SYNCDSI_EN            (uint8)((uint8)0x0Fu << ServoCD_SYNCDSI_SHIFT)


#else
    #define ServoCD_STATUS                (*(reg8 *)   ServoCD_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ServoCD_STATUS_PTR            ((reg8 *)    ServoCD_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ServoCD_STATUS_MASK           (*(reg8 *)   ServoCD_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ServoCD_STATUS_MASK_PTR       ((reg8 *)    ServoCD_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ServoCD_STATUS_AUX_CTRL       (*(reg8 *)   ServoCD_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define ServoCD_CONTROL               (*(reg8 *)   ServoCD_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define ServoCD_CONTROL_PTR           ((reg8 *)    ServoCD_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define ServoCD_CTRL_ENABLE_SHIFT      (0x07u)
    #define ServoCD_CTRL_RESET_SHIFT       (0x06u)
    #define ServoCD_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define ServoCD_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define ServoCD_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define ServoCD_CTRL_ENABLE            (uint8)((uint8)0x01u << ServoCD_CTRL_ENABLE_SHIFT)
    #define ServoCD_CTRL_RESET             (uint8)((uint8)0x01u << ServoCD_CTRL_RESET_SHIFT)
    #define ServoCD_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ServoCD_CTRL_CMPMODE2_SHIFT)
    #define ServoCD_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ServoCD_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define ServoCD_STATUS_KILL_SHIFT          (0x05u)
    #define ServoCD_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define ServoCD_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define ServoCD_STATUS_TC_SHIFT            (0x02u)
    #define ServoCD_STATUS_CMP2_SHIFT          (0x01u)
    #define ServoCD_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ServoCD_STATUS_KILL_INT_EN_MASK_SHIFT          (ServoCD_STATUS_KILL_SHIFT)
    #define ServoCD_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (ServoCD_STATUS_FIFONEMPTY_SHIFT)
    #define ServoCD_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (ServoCD_STATUS_FIFOFULL_SHIFT)
    #define ServoCD_STATUS_TC_INT_EN_MASK_SHIFT            (ServoCD_STATUS_TC_SHIFT)
    #define ServoCD_STATUS_CMP2_INT_EN_MASK_SHIFT          (ServoCD_STATUS_CMP2_SHIFT)
    #define ServoCD_STATUS_CMP1_INT_EN_MASK_SHIFT          (ServoCD_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define ServoCD_STATUS_KILL            (uint8)((uint8)0x00u << ServoCD_STATUS_KILL_SHIFT )
    #define ServoCD_STATUS_FIFOFULL        (uint8)((uint8)0x01u << ServoCD_STATUS_FIFOFULL_SHIFT)
    #define ServoCD_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << ServoCD_STATUS_FIFONEMPTY_SHIFT)
    #define ServoCD_STATUS_TC              (uint8)((uint8)0x01u << ServoCD_STATUS_TC_SHIFT)
    #define ServoCD_STATUS_CMP2            (uint8)((uint8)0x01u << ServoCD_STATUS_CMP2_SHIFT)
    #define ServoCD_STATUS_CMP1            (uint8)((uint8)0x01u << ServoCD_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ServoCD_STATUS_KILL_INT_EN_MASK            (ServoCD_STATUS_KILL)
    #define ServoCD_STATUS_FIFOFULL_INT_EN_MASK        (ServoCD_STATUS_FIFOFULL)
    #define ServoCD_STATUS_FIFONEMPTY_INT_EN_MASK      (ServoCD_STATUS_FIFONEMPTY)
    #define ServoCD_STATUS_TC_INT_EN_MASK              (ServoCD_STATUS_TC)
    #define ServoCD_STATUS_CMP2_INT_EN_MASK            (ServoCD_STATUS_CMP2)
    #define ServoCD_STATUS_CMP1_INT_EN_MASK            (ServoCD_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define ServoCD_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define ServoCD_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define ServoCD_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define ServoCD_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define ServoCD_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* ServoCD_UsingFixedFunction */

#endif  /* CY_PWM_ServoCD_H */


/* [] END OF FILE */
