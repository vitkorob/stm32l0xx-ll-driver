/**
  ******************************************************************************
  * @file    stm32l0xx_ll_irq.c
  * @author  Victor Korobkovsky
  * @brief   IRQ LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_ll_irq.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup STM32L0xx_LL_Driver
  * @{
  */

/** @addtogroup IRQ_LL
  * @brief IRQ LL module driver
  * @{
  */

/** @addtogroup IRQ_Private
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/**
  * @brief  Checking the alignment of the RAM table
  * @param  VECTORS: pointer to the RAM table.
  * @retval None
  */
#define IS_VECTORS_ALIGNED(VECTORS)   (((uint32_t)VECTORS & 0xFF) == 0)

/* Private variables ---------------------------------------------------------*/
/**
  * @brief  RAM table.
  */
#if defined (__ICCARM__)
  #pragma data_alignment=256
static __no_init void (*Vectors[IRQ_TOTAL])(void) @ "VTABLE";
#elif defined (__GNUC__)
static __attribute__((section(".noinit"))) void (*Vectors[IRQ_TOTAL])(void) __attribute__((aligned(256)));
#else
 #error "No implementation for this compiler"
#endif

/* Private function prototypes -----------------------------------------------*/
static void IntDefaultHandler(void);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup IRQ_Exported_Functions
  * @{
  */

/** @addtogroup IRQ_Exported_Functions_Group1
  * @brief  Initialization and Configuration functions. 
  * @{
  */

/**
  * @brief  Assigns a function to handle the interrupt.
  * @attention  On the first call, it copies the interrupt vector table to the RAM of the MCU,
  *             then makes a change to the interrupt handler. On subsequent calls,
  *             only the interrupt handlers are replaced.
  * @param  IRQn: The ID of the interrupt.
  * @param  Handler: Pointer to a function.
  * @retval None
  */
ErrorStatus LL_IRQ_Init(IRQn_Type IRQn, void (*Handler)(void))
{
  /* Check the parameters */
  assert_param(IS_IRQ_NUM(IRQn));
  assert_param(IS_VECTORS_ALIGNED(Vectors));

  /*
   * See if the RAM vector table has been initialized.
   */
  if (SCB->VTOR != (uint32_t)Vectors)
  {
    uint32_t *Source  = (uint32_t *)SCB->VTOR;
    uint32_t *Dest    = (uint32_t *)Vectors;
    uint32_t n        = IRQ_TOTAL;

    /*
     * Copy the vector table from the beginning of FLASH
     * to the RAM vector table.
     */
    while (n--)
    {
      *Dest++ = *Source++;
    }

    /*
     * Point the NVIC at the RAM vector table.
     */
    SCB->VTOR = (uint32_t)Vectors;
  }

  /*
   * Save the interrupt handler.
   */
  Vectors[IRQ_NUM(IRQn)] = Handler;

  return SUCCESS;
}

/**
  * @brief  Assigns a stub function (infinite loop) to handle the interrupt.
  * @attention  Before calling this function, the corresponding interrupt must be deactivated,
  *             otherwise it may cause the entire program of the microcontroller to hang.
  * @param  IRQn: The ID of the interrupt.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Interrupt is de-initialized
  *          - ERROR: Interrupt is not de-initialized
  */
ErrorStatus LL_IRQ_DeInit(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_IRQ_NUM(IRQn));

  /*
   * Reset the interrupt handler.
   */
  Vectors[IRQ_NUM(IRQn)] = IntDefaultHandler;

  return SUCCESS;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup IRQ_Private
  * @{
  */
/**
  * @brief  Default interrupt handler for all interrupts.
  *
  * It simply loops forever so that the system state is preserved
  * for observation by a debugger. Since interrupts should be disabled
  * before unregistering the corresponding handler, this should never be called.
  *
  * @retval None
  */
static void IntDefaultHandler(void)
{
  while (1)
  {
    // Capture
  }
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

