/*******************************************************************************
* File Name: ServoAB.h
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

#if !defined(CY_PWM_ServoAB_H)
#define CY_PWM_ServoAB_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ServoAB_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define ServoAB_Resolution                     (16u)
#define ServoAB_UsingFixedFunction             (0u)
#define ServoAB_DeadBandMode                   (0u)
#define ServoAB_KillModeMinTime                (0u)
#define ServoAB_KillMode                       (0u)
#define ServoAB_PWMMode                        (1u)
#define ServoAB_PWMModeIsCenterAligned         (0u)
#define ServoAB_DeadBandUsed                   (0u)
#define ServoAB_DeadBand2_4                    (0u)

#if !defined(ServoAB_PWMUDB_genblk8_stsreg__REMOVED)
    #define ServoAB_UseStatus                  (1u)
#else
    #define ServoAB_UseStatus                  (0u)
#endif /* !defined(ServoAB_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(ServoAB_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define ServoAB_UseControl                 (1u)
#else
    #define ServoAB_UseControl                 (0u)
#endif /* !defined(ServoAB_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define ServoAB_UseOneCompareMode              (0u)
#define ServoAB_MinimumKillTime                (1u)
#define ServoAB_EnableMode                     (0u)

#define ServoAB_CompareMode1SW                 (0u)
#define ServoAB_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define ServoAB__B_PWM__DISABLED 0
#define ServoAB__B_PWM__ASYNCHRONOUS 1
#define ServoAB__B_PWM__SINGLECYCLE 2
#define ServoAB__B_PWM__LATCHED 3
#define ServoAB__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define ServoAB__B_PWM__DBMDISABLED 0
#define ServoAB__B_PWM__DBM_2_4_CLOCKS 1
#define ServoAB__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define ServoAB__B_PWM__ONE_OUTPUT 0
#define ServoAB__B_PWM__TWO_OUTPUTS 1
#define ServoAB__B_PWM__DUAL_EDGE 2
#define ServoAB__B_PWM__CENTER_ALIGN 3
#define ServoAB__B_PWM__DITHER 5
#define ServoAB__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define ServoAB__B_PWM__LESS_THAN 1
#define ServoAB__B_PWM__LESS_THAN_OR_EQUAL 2
#define ServoAB__B_PWM__GREATER_THAN 3
#define ServoAB__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define ServoAB__B_PWM__EQUAL 0
#define ServoAB__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!ServoAB_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!ServoAB_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!ServoAB_PWMModeIsCenterAligned) */
        #if (ServoAB_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (ServoAB_UseStatus) */

        /* Backup for Deadband parameters */
        #if(ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_256_CLOCKS || \
            ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(ServoAB_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (ServoAB_KillModeMinTime) */

        /* Backup control register */
        #if(ServoAB_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (ServoAB_UseControl) */

    #endif /* (!ServoAB_UsingFixedFunction) */

}ServoAB_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    ServoAB_Start(void) ;
void    ServoAB_Stop(void) ;

#if (ServoAB_UseStatus || ServoAB_UsingFixedFunction)
    void  ServoAB_SetInterruptMode(uint8 interruptMode) ;
    uint8 ServoAB_ReadStatusRegister(void) ;
#endif /* (ServoAB_UseStatus || ServoAB_UsingFixedFunction) */

#define ServoAB_GetInterruptSource() ServoAB_ReadStatusRegister()

#if (ServoAB_UseControl)
    uint8 ServoAB_ReadControlRegister(void) ;
    void  ServoAB_WriteControlRegister(uint8 control)
          ;
#endif /* (ServoAB_UseControl) */

#if (ServoAB_UseOneCompareMode)
   #if (ServoAB_CompareMode1SW)
       void    ServoAB_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (ServoAB_CompareMode1SW) */
#else
    #if (ServoAB_CompareMode1SW)
        void    ServoAB_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (ServoAB_CompareMode1SW) */
    #if (ServoAB_CompareMode2SW)
        void    ServoAB_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (ServoAB_CompareMode2SW) */
#endif /* (ServoAB_UseOneCompareMode) */

#if (!ServoAB_UsingFixedFunction)
    uint16   ServoAB_ReadCounter(void) ;
    uint16 ServoAB_ReadCapture(void) ;

    #if (ServoAB_UseStatus)
            void ServoAB_ClearFIFO(void) ;
    #endif /* (ServoAB_UseStatus) */

    void    ServoAB_WriteCounter(uint16 counter)
            ;
#endif /* (!ServoAB_UsingFixedFunction) */

void    ServoAB_WritePeriod(uint16 period)
        ;
uint16 ServoAB_ReadPeriod(void) ;

#if (ServoAB_UseOneCompareMode)
    void    ServoAB_WriteCompare(uint16 compare)
            ;
    uint16 ServoAB_ReadCompare(void) ;
#else
    void    ServoAB_WriteCompare1(uint16 compare)
            ;
    uint16 ServoAB_ReadCompare1(void) ;
    void    ServoAB_WriteCompare2(uint16 compare)
            ;
    uint16 ServoAB_ReadCompare2(void) ;
#endif /* (ServoAB_UseOneCompareMode) */


#if (ServoAB_DeadBandUsed)
    void    ServoAB_WriteDeadTime(uint8 deadtime) ;
    uint8   ServoAB_ReadDeadTime(void) ;
#endif /* (ServoAB_DeadBandUsed) */

#if ( ServoAB_KillModeMinTime)
    void ServoAB_WriteKillTime(uint8 killtime) ;
    uint8 ServoAB_ReadKillTime(void) ;
#endif /* ( ServoAB_KillModeMinTime) */

void ServoAB_Init(void) ;
void ServoAB_Enable(void) ;
void ServoAB_Sleep(void) ;
void ServoAB_Wakeup(void) ;
void ServoAB_SaveConfig(void) ;
void ServoAB_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define ServoAB_INIT_PERIOD_VALUE          (24000u)
#define ServoAB_INIT_COMPARE_VALUE1        (0u)
#define ServoAB_INIT_COMPARE_VALUE2        (0u)
#define ServoAB_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    ServoAB_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ServoAB_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ServoAB_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ServoAB_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define ServoAB_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  ServoAB_CTRL_CMPMODE2_SHIFT)
#define ServoAB_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  ServoAB_CTRL_CMPMODE1_SHIFT)
#define ServoAB_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (ServoAB_UsingFixedFunction)
   #define ServoAB_PERIOD_LSB              (*(reg16 *) ServoAB_PWMHW__PER0)
   #define ServoAB_PERIOD_LSB_PTR          ( (reg16 *) ServoAB_PWMHW__PER0)
   #define ServoAB_COMPARE1_LSB            (*(reg16 *) ServoAB_PWMHW__CNT_CMP0)
   #define ServoAB_COMPARE1_LSB_PTR        ( (reg16 *) ServoAB_PWMHW__CNT_CMP0)
   #define ServoAB_COMPARE2_LSB            (0x00u)
   #define ServoAB_COMPARE2_LSB_PTR        (0x00u)
   #define ServoAB_COUNTER_LSB             (*(reg16 *) ServoAB_PWMHW__CNT_CMP0)
   #define ServoAB_COUNTER_LSB_PTR         ( (reg16 *) ServoAB_PWMHW__CNT_CMP0)
   #define ServoAB_CAPTURE_LSB             (*(reg16 *) ServoAB_PWMHW__CAP0)
   #define ServoAB_CAPTURE_LSB_PTR         ( (reg16 *) ServoAB_PWMHW__CAP0)
   #define ServoAB_RT1                     (*(reg8 *)  ServoAB_PWMHW__RT1)
   #define ServoAB_RT1_PTR                 ( (reg8 *)  ServoAB_PWMHW__RT1)

#else
   #if (ServoAB_Resolution == 8u) /* 8bit - PWM */

       #if(ServoAB_PWMModeIsCenterAligned)
           #define ServoAB_PERIOD_LSB      (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define ServoAB_PERIOD_LSB_PTR  ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define ServoAB_PERIOD_LSB      (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define ServoAB_PERIOD_LSB_PTR  ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (ServoAB_PWMModeIsCenterAligned) */

       #define ServoAB_COMPARE1_LSB        (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define ServoAB_COMPARE1_LSB_PTR    ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define ServoAB_COMPARE2_LSB        (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define ServoAB_COMPARE2_LSB_PTR    ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define ServoAB_COUNTERCAP_LSB      (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define ServoAB_COUNTERCAP_LSB_PTR  ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define ServoAB_COUNTER_LSB         (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define ServoAB_COUNTER_LSB_PTR     ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define ServoAB_CAPTURE_LSB         (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define ServoAB_CAPTURE_LSB_PTR     ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(ServoAB_PWMModeIsCenterAligned)
               #define ServoAB_PERIOD_LSB      (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define ServoAB_PERIOD_LSB_PTR  ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define ServoAB_PERIOD_LSB      (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define ServoAB_PERIOD_LSB_PTR  ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (ServoAB_PWMModeIsCenterAligned) */

            #define ServoAB_COMPARE1_LSB       (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define ServoAB_COMPARE1_LSB_PTR   ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define ServoAB_COMPARE2_LSB       (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define ServoAB_COMPARE2_LSB_PTR   ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define ServoAB_COUNTERCAP_LSB     (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define ServoAB_COUNTERCAP_LSB_PTR ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define ServoAB_COUNTER_LSB        (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define ServoAB_COUNTER_LSB_PTR    ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define ServoAB_CAPTURE_LSB        (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define ServoAB_CAPTURE_LSB_PTR    ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(ServoAB_PWMModeIsCenterAligned)
               #define ServoAB_PERIOD_LSB      (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define ServoAB_PERIOD_LSB_PTR  ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define ServoAB_PERIOD_LSB      (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define ServoAB_PERIOD_LSB_PTR  ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (ServoAB_PWMModeIsCenterAligned) */

            #define ServoAB_COMPARE1_LSB       (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define ServoAB_COMPARE1_LSB_PTR   ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define ServoAB_COMPARE2_LSB       (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define ServoAB_COMPARE2_LSB_PTR   ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define ServoAB_COUNTERCAP_LSB     (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define ServoAB_COUNTERCAP_LSB_PTR ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define ServoAB_COUNTER_LSB        (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define ServoAB_COUNTER_LSB_PTR    ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define ServoAB_CAPTURE_LSB        (*(reg16 *) ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define ServoAB_CAPTURE_LSB_PTR    ((reg16 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define ServoAB_AUX_CONTROLDP1          (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define ServoAB_AUX_CONTROLDP1_PTR      ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (ServoAB_Resolution == 8) */

   #define ServoAB_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define ServoAB_AUX_CONTROLDP0          (*(reg8 *)  ServoAB_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define ServoAB_AUX_CONTROLDP0_PTR      ((reg8 *)   ServoAB_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (ServoAB_UsingFixedFunction) */

#if(ServoAB_KillModeMinTime )
    #define ServoAB_KILLMODEMINTIME        (*(reg8 *)  ServoAB_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define ServoAB_KILLMODEMINTIME_PTR    ((reg8 *)   ServoAB_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (ServoAB_KillModeMinTime ) */

#if(ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_256_CLOCKS)
    #define ServoAB_DEADBAND_COUNT         (*(reg8 *)  ServoAB_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ServoAB_DEADBAND_COUNT_PTR     ((reg8 *)   ServoAB_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ServoAB_DEADBAND_LSB_PTR       ((reg8 *)   ServoAB_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define ServoAB_DEADBAND_LSB           (*(reg8 *)  ServoAB_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (ServoAB_UsingFixedFunction)
        #define ServoAB_DEADBAND_COUNT         (*(reg8 *)  ServoAB_PWMHW__CFG0)
        #define ServoAB_DEADBAND_COUNT_PTR     ((reg8 *)   ServoAB_PWMHW__CFG0)
        #define ServoAB_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ServoAB_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define ServoAB_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define ServoAB_DEADBAND_COUNT         (*(reg8 *)  ServoAB_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ServoAB_DEADBAND_COUNT_PTR     ((reg8 *)   ServoAB_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ServoAB_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ServoAB_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define ServoAB_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (ServoAB_UsingFixedFunction) */
#endif /* (ServoAB_DeadBandMode == ServoAB__B_PWM__DBM_256_CLOCKS) */



#if (ServoAB_UsingFixedFunction)
    #define ServoAB_STATUS                 (*(reg8 *) ServoAB_PWMHW__SR0)
    #define ServoAB_STATUS_PTR             ((reg8 *) ServoAB_PWMHW__SR0)
    #define ServoAB_STATUS_MASK            (*(reg8 *) ServoAB_PWMHW__SR0)
    #define ServoAB_STATUS_MASK_PTR        ((reg8 *) ServoAB_PWMHW__SR0)
    #define ServoAB_CONTROL                (*(reg8 *) ServoAB_PWMHW__CFG0)
    #define ServoAB_CONTROL_PTR            ((reg8 *) ServoAB_PWMHW__CFG0)
    #define ServoAB_CONTROL2               (*(reg8 *) ServoAB_PWMHW__CFG1)
    #define ServoAB_CONTROL3               (*(reg8 *) ServoAB_PWMHW__CFG2)
    #define ServoAB_GLOBAL_ENABLE          (*(reg8 *) ServoAB_PWMHW__PM_ACT_CFG)
    #define ServoAB_GLOBAL_ENABLE_PTR      ( (reg8 *) ServoAB_PWMHW__PM_ACT_CFG)
    #define ServoAB_GLOBAL_STBY_ENABLE     (*(reg8 *) ServoAB_PWMHW__PM_STBY_CFG)
    #define ServoAB_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) ServoAB_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define ServoAB_BLOCK_EN_MASK          (ServoAB_PWMHW__PM_ACT_MSK)
    #define ServoAB_BLOCK_STBY_EN_MASK     (ServoAB_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define ServoAB_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define ServoAB_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define ServoAB_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define ServoAB_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define ServoAB_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define ServoAB_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define ServoAB_CTRL_ENABLE            (uint8)((uint8)0x01u << ServoAB_CTRL_ENABLE_SHIFT)
    #define ServoAB_CTRL_RESET             (uint8)((uint8)0x01u << ServoAB_CTRL_RESET_SHIFT)
    #define ServoAB_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ServoAB_CTRL_CMPMODE2_SHIFT)
    #define ServoAB_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ServoAB_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ServoAB_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define ServoAB_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << ServoAB_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define ServoAB_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define ServoAB_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define ServoAB_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define ServoAB_STATUS_TC_INT_EN_MASK_SHIFT            (ServoAB_STATUS_TC_SHIFT - 4u)
    #define ServoAB_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define ServoAB_STATUS_CMP1_INT_EN_MASK_SHIFT          (ServoAB_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define ServoAB_STATUS_TC              (uint8)((uint8)0x01u << ServoAB_STATUS_TC_SHIFT)
    #define ServoAB_STATUS_CMP1            (uint8)((uint8)0x01u << ServoAB_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define ServoAB_STATUS_TC_INT_EN_MASK              (uint8)((uint8)ServoAB_STATUS_TC >> 4u)
    #define ServoAB_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)ServoAB_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define ServoAB_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define ServoAB_RT1_MASK              (uint8)((uint8)0x03u << ServoAB_RT1_SHIFT)
    #define ServoAB_SYNC                  (uint8)((uint8)0x03u << ServoAB_RT1_SHIFT)
    #define ServoAB_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define ServoAB_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << ServoAB_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define ServoAB_SYNCDSI_EN            (uint8)((uint8)0x0Fu << ServoAB_SYNCDSI_SHIFT)


#else
    #define ServoAB_STATUS                (*(reg8 *)   ServoAB_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ServoAB_STATUS_PTR            ((reg8 *)    ServoAB_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ServoAB_STATUS_MASK           (*(reg8 *)   ServoAB_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ServoAB_STATUS_MASK_PTR       ((reg8 *)    ServoAB_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ServoAB_STATUS_AUX_CTRL       (*(reg8 *)   ServoAB_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define ServoAB_CONTROL               (*(reg8 *)   ServoAB_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define ServoAB_CONTROL_PTR           ((reg8 *)    ServoAB_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define ServoAB_CTRL_ENABLE_SHIFT      (0x07u)
    #define ServoAB_CTRL_RESET_SHIFT       (0x06u)
    #define ServoAB_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define ServoAB_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define ServoAB_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define ServoAB_CTRL_ENABLE            (uint8)((uint8)0x01u << ServoAB_CTRL_ENABLE_SHIFT)
    #define ServoAB_CTRL_RESET             (uint8)((uint8)0x01u << ServoAB_CTRL_RESET_SHIFT)
    #define ServoAB_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ServoAB_CTRL_CMPMODE2_SHIFT)
    #define ServoAB_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ServoAB_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define ServoAB_STATUS_KILL_SHIFT          (0x05u)
    #define ServoAB_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define ServoAB_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define ServoAB_STATUS_TC_SHIFT            (0x02u)
    #define ServoAB_STATUS_CMP2_SHIFT          (0x01u)
    #define ServoAB_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ServoAB_STATUS_KILL_INT_EN_MASK_SHIFT          (ServoAB_STATUS_KILL_SHIFT)
    #define ServoAB_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (ServoAB_STATUS_FIFONEMPTY_SHIFT)
    #define ServoAB_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (ServoAB_STATUS_FIFOFULL_SHIFT)
    #define ServoAB_STATUS_TC_INT_EN_MASK_SHIFT            (ServoAB_STATUS_TC_SHIFT)
    #define ServoAB_STATUS_CMP2_INT_EN_MASK_SHIFT          (ServoAB_STATUS_CMP2_SHIFT)
    #define ServoAB_STATUS_CMP1_INT_EN_MASK_SHIFT          (ServoAB_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define ServoAB_STATUS_KILL            (uint8)((uint8)0x00u << ServoAB_STATUS_KILL_SHIFT )
    #define ServoAB_STATUS_FIFOFULL        (uint8)((uint8)0x01u << ServoAB_STATUS_FIFOFULL_SHIFT)
    #define ServoAB_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << ServoAB_STATUS_FIFONEMPTY_SHIFT)
    #define ServoAB_STATUS_TC              (uint8)((uint8)0x01u << ServoAB_STATUS_TC_SHIFT)
    #define ServoAB_STATUS_CMP2            (uint8)((uint8)0x01u << ServoAB_STATUS_CMP2_SHIFT)
    #define ServoAB_STATUS_CMP1            (uint8)((uint8)0x01u << ServoAB_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ServoAB_STATUS_KILL_INT_EN_MASK            (ServoAB_STATUS_KILL)
    #define ServoAB_STATUS_FIFOFULL_INT_EN_MASK        (ServoAB_STATUS_FIFOFULL)
    #define ServoAB_STATUS_FIFONEMPTY_INT_EN_MASK      (ServoAB_STATUS_FIFONEMPTY)
    #define ServoAB_STATUS_TC_INT_EN_MASK              (ServoAB_STATUS_TC)
    #define ServoAB_STATUS_CMP2_INT_EN_MASK            (ServoAB_STATUS_CMP2)
    #define ServoAB_STATUS_CMP1_INT_EN_MASK            (ServoAB_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define ServoAB_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define ServoAB_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define ServoAB_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define ServoAB_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define ServoAB_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* ServoAB_UsingFixedFunction */

#endif  /* CY_PWM_ServoAB_H */


/* [] END OF FILE */
