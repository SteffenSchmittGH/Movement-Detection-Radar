/*******************************************************************************
* File Name: DAC.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DAC_H) /* Pins DAC_H */
#define CY_PINS_DAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DAC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DAC__PORT == 15 && ((DAC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DAC_Write(uint8 value);
void    DAC_SetDriveMode(uint8 mode);
uint8   DAC_ReadDataReg(void);
uint8   DAC_Read(void);
void    DAC_SetInterruptMode(uint16 position, uint16 mode);
uint8   DAC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DAC_SetDriveMode() function.
     *  @{
     */
        #define DAC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DAC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DAC_DM_RES_UP          PIN_DM_RES_UP
        #define DAC_DM_RES_DWN         PIN_DM_RES_DWN
        #define DAC_DM_OD_LO           PIN_DM_OD_LO
        #define DAC_DM_OD_HI           PIN_DM_OD_HI
        #define DAC_DM_STRONG          PIN_DM_STRONG
        #define DAC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DAC_MASK               DAC__MASK
#define DAC_SHIFT              DAC__SHIFT
#define DAC_WIDTH              1u

/* Interrupt constants */
#if defined(DAC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DAC_SetInterruptMode() function.
     *  @{
     */
        #define DAC_INTR_NONE      (uint16)(0x0000u)
        #define DAC_INTR_RISING    (uint16)(0x0001u)
        #define DAC_INTR_FALLING   (uint16)(0x0002u)
        #define DAC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DAC_INTR_MASK      (0x01u) 
#endif /* (DAC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DAC_PS                     (* (reg8 *) DAC__PS)
/* Data Register */
#define DAC_DR                     (* (reg8 *) DAC__DR)
/* Port Number */
#define DAC_PRT_NUM                (* (reg8 *) DAC__PRT) 
/* Connect to Analog Globals */                                                  
#define DAC_AG                     (* (reg8 *) DAC__AG)                       
/* Analog MUX bux enable */
#define DAC_AMUX                   (* (reg8 *) DAC__AMUX) 
/* Bidirectional Enable */                                                        
#define DAC_BIE                    (* (reg8 *) DAC__BIE)
/* Bit-mask for Aliased Register Access */
#define DAC_BIT_MASK               (* (reg8 *) DAC__BIT_MASK)
/* Bypass Enable */
#define DAC_BYP                    (* (reg8 *) DAC__BYP)
/* Port wide control signals */                                                   
#define DAC_CTL                    (* (reg8 *) DAC__CTL)
/* Drive Modes */
#define DAC_DM0                    (* (reg8 *) DAC__DM0) 
#define DAC_DM1                    (* (reg8 *) DAC__DM1)
#define DAC_DM2                    (* (reg8 *) DAC__DM2) 
/* Input Buffer Disable Override */
#define DAC_INP_DIS                (* (reg8 *) DAC__INP_DIS)
/* LCD Common or Segment Drive */
#define DAC_LCD_COM_SEG            (* (reg8 *) DAC__LCD_COM_SEG)
/* Enable Segment LCD */
#define DAC_LCD_EN                 (* (reg8 *) DAC__LCD_EN)
/* Slew Rate Control */
#define DAC_SLW                    (* (reg8 *) DAC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DAC_PRTDSI__CAPS_SEL       (* (reg8 *) DAC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DAC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DAC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DAC_PRTDSI__OE_SEL0        (* (reg8 *) DAC__PRTDSI__OE_SEL0) 
#define DAC_PRTDSI__OE_SEL1        (* (reg8 *) DAC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DAC_PRTDSI__OUT_SEL0       (* (reg8 *) DAC__PRTDSI__OUT_SEL0) 
#define DAC_PRTDSI__OUT_SEL1       (* (reg8 *) DAC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DAC_PRTDSI__SYNC_OUT       (* (reg8 *) DAC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DAC__SIO_CFG)
    #define DAC_SIO_HYST_EN        (* (reg8 *) DAC__SIO_HYST_EN)
    #define DAC_SIO_REG_HIFREQ     (* (reg8 *) DAC__SIO_REG_HIFREQ)
    #define DAC_SIO_CFG            (* (reg8 *) DAC__SIO_CFG)
    #define DAC_SIO_DIFF           (* (reg8 *) DAC__SIO_DIFF)
#endif /* (DAC__SIO_CFG) */

/* Interrupt Registers */
#if defined(DAC__INTSTAT)
    #define DAC_INTSTAT            (* (reg8 *) DAC__INTSTAT)
    #define DAC_SNAP               (* (reg8 *) DAC__SNAP)
    
	#define DAC_0_INTTYPE_REG 		(* (reg8 *) DAC__0__INTTYPE)
#endif /* (DAC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DAC_H */


/* [] END OF FILE */
