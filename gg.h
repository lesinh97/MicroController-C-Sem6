#ifndef __GG_H
#define __GG_H

#define PORT_BASE           ((uint32_t)0x40000000) /*!< Ðia chi co so cua thiet bi ngoai vi */
#define AHBPORT_BASE        (PORT_BASE + 0x20000)
#define A_BASE            (AHBPORT_BASE + 0x0000)
#define B_BASE            (AHBPORT_BASE + 0x0400)




typedef struct
{
  __IO uint32_t MODER;
  __IO uint16_t OTYPER;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __IO uint16_t IDR;
  __IO uint16_t ODR;
} PORT_GP_TypeDef;

#define GPIOA               ((PORT_GP_TypeDef *) A_BASE)
#define GPIOB               ((PORT_GP_TypeDef *) B_BASE)

/******************  Cac bit cho thanh ghi RCC_AHBENR  ******************/
#define  RcAh_GPIOAEN                  ((uint32_t)0x00000001)        /*!< Port A */
#define  RcAh_GPIOBEN                  ((uint32_t)0x00000002)        /*!< Port B*/


#define __NVIC_PRIORITY          4  /* chip su dung 4bit cho level piority*/
/*****************  Cac gia tri bit cho thanh ghi Systick_CTRL  *****************/
#define  SysTick_CTRL_EN                 ((uint32_t)0x00000001)        /*!< enable counter cho systick */
#define  SysTick_CTRL_TICKINT                ((uint32_t)0x00000002)        /*!< systick có xu huong count ve 0 */
#define  SysTick_CTRL_HzSOURCE              ((uint32_t)0x00000004)        /*!< clock ban dau */

#endif