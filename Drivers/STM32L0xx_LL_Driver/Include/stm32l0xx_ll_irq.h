/**
  ******************************************************************************
  * @file    stm32l0xx_ll_irq.h
  * @author  Victor Korobkovsky
  * @brief   Header file of IRQ LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_LL_IRQ_H
#define __STM32L0xx_LL_IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx.h"

/** @addtogroup STM32L0xx_LL_Driver
  * @{
  */

/** @defgroup IRQ_LL IRQ
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/
/** @defgroup IRQ_Exported_Constants   IRQ Exported Constants
  * @{
  */
#if defined(STM32L011xx)
  #define IRQ_TOTAL 48
#elif defined(STM32L021xx)
  #define IRQ_TOTAL 48
#elif defined(STM32L031xx)
  #define IRQ_TOTAL 48
#elif defined(STM32L041xx)
  #define IRQ_TOTAL 48
#elif defined(STM32L051xx) || defined(STM32L052xx) || defined(STM32L053xx)
  #define IRQ_TOTAL 48
#elif defined(STM32L062xx) || defined(STM32L063xx) || defined(STM32L061xx)
  #define IRQ_TOTAL 48
#elif defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx)
  #define IRQ_TOTAL 48
#elif defined(STM32L082xx) || defined(STM32L083xx) || defined(STM32L081xx)
  #define IRQ_TOTAL 48
#else
 #error "Please select first the target STM32L0xx device used in your application (in stm32l0xx.h file)"
#endif

/**
  * @}
  */

/** @defgroup  IRQ_Private_Macros   IRQ Private Macros
  * @{
  */
/* Private macros --------------------------------------------------------*/

/**
  * @brief  Получение системного порядкового номера прерывания, с учетом исключений.
  * @param  IRQ: Номер по стандарту CMSIS.
  * @retval None
  */
#define IRQ_NUM(IRQ)  ((int32_t)IRQ + 16)

/**
  * @brief  Checks if IRQn parameter is in allowed range.
  * @param  IRQn: specifies the interrupt.
  * @retval None
  */
#define IS_IRQ_NUM(IRQn)  (IRQ_NUM(IRQn) < IRQ_TOTAL)
/**
  * @}
  */

/** @defgroup IRQ_Exported_Functions IRQ Exported Functions
  * @{
  */
/* Exported functions --------------------------------------------------------*/

/** @defgroup IRQ_Exported_Functions_Group1 Initialization/de-initialization functions
  * @{
  */
/* Initialization and de-initialization functions  ****************************/
ErrorStatus LL_IRQ_Init(IRQn_Type IRQn, void (*Handler)(void));
ErrorStatus LL_IRQ_DeInit(IRQn_Type IRQn);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_LL_IRQ_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

