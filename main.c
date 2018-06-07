//******************** (C) Yifeng ZHU ********************
// @file    main.c
// @author  Yifeng Zhu
// @version V1.0.0
// @date    November-11-2012
// @note    
// @brief   C code for STM32L1xx Discovery Kit
// @note
//          This code is for the book "Embedded Systems with ARM Cortex-M3 
//          Microcontrollers in Assembly Language and C, Yifeng Zhu, 
//          ISBN-10: 0982692625.
// @attension
//          This code is provided for education purpose. The author shall not be 
//          held liable for any direct, indirect or consequential damages, for any 
//          reason whatever. More information can be found from book website: 
//          http://www.eece.maine.edu/~zhu/book
//********************************************************

#include <stdint.h>

/* Standard STM32L1xxx driver headers */
#include "stm32l1xx.h"
//#include "gg.h"

/* STM32L1xx Discovery Kit:
    - USER Pushbutton: connected to PA0 (GPIO Port A, PIN 0), CLK RCC_AHBENR_GPIOAEN
    - RESET Pushbutton: connected RESET
    - GREEN LED: connected to PB7 (GPIO Port B, PIN 7), CLK RCC_AHBENR_GPIOBEN 
    - BLUE LED: connected to PB6 (GPIO Port B, PIN 6), CLK RCC_AHBENR_GPIOBEN
    - Linear touch sensor/touchkeys: PA6, PA7 (group 2),  PC4, PC5 (group 9),  PB0, PB1 (group 3)
*/



//******************************************************************************************
//* The main program starts here
//******************************************************************************************
// TimingDelay doc tu phan cung
static __IO uint32_t TimingDelay;
void Systick_init (uint32_t ticks)
{
	//RCC->ICSCR |= RCC_ICSCR_MSIRANGE_5; //Hay doc defination de biet them chi tiet
	
	// tat systick IRQ va bo dem Systick
	SysTick->CTRL =0;
	
	// set reload regis
	SysTick->LOAD = ticks -1;
	
	// set piority
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) -1);
	
	//reset gia tri bo dem systick
	SysTick->VAL =0;
	
	// set xung nhip processor
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE; 
	//external
	//SysTick->CTRL &= ~(1<<3);
	
	//enable systick IRQ va systick timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	
	//enable yeu cau ngoai le cho systick
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
}
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}
	
void SysTick_Handler(void)
{
	//if (TimingDelay !=0) // khong cho no la so am
	//{
	//	TimingDelay--; // thuc hien phep tru ve 0
	//}
	GPIOB->ODR ^= 1<<6; //dao led
	GPIOB->ODR ^=	1<<7;	//dao led 
} 

	
void GPIO_Clock_Enable(){
	//enable clock cho port A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	// Enable clock cho port B
	RCC->AHBENR |= 0x00000002; // dung RCC_AHBENR_GPIOBEN cung duoc 
}
void GPIO_Pin_Init(){

	
	// set pin 6, pin 7 la GPIO
	// 00 = digital in(default), 01 = digital output
	// 10 = ham thay the, 11 = analog
	GPIOB->MODER &= ~(0x03<<(2*6)); 	// tao mode mask cho pin 6
	GPIOB->MODER |= 0x01<<(2*6);				// set pin 6 la digital output
	GPIOB->MODER &= ~(0x03<<(2*7)); 	// tao mode mask cho pin 7
	GPIOB->MODER |= 0x01<<(2*7);				// set pin 7 la digital output
	
	
	// set pin 0 i/o la GPIO
	// input(00, default), output(01), alternative fucntion(10), analog(11)
	GPIOA->MODER &= ~(0x03);
	
	
	// set pin 6 la push-pull
	// 0 = push-pull(0, default), 1 = open-drain
	GPIOB->OTYPER &= ~(1<<6);
	// set pin 7 la push-pull
	// 0 = push-pull(0, default), 1 = open-drain
	GPIOB->OTYPER &= ~(1<<7);
	// set pin 0 la output push-pull
	GPIOA->OTYPER &= ~(0x1);
	
	
	
	// set i/o toc do cong ra
	// 00 = 400KHz, 01 = 2MHz, 10 = 10MHz, 11 = 40MHz
	GPIOB->OSPEEDR &= ~(0x03<<(2*6)); // toc do cua mask 6
	GPIOB->OSPEEDR |= 0x01<<(2*6);
	GPIOB->OSPEEDR &= ~(0x03<<(2*7)); // toc do cua mask 7
	GPIOB->OSPEEDR |= 0x01<<(2*7);
	// set i/o output speed la 2MHz 
	GPIOA->OSPEEDR &= ~(0x03);	// toc do mask
	GPIOA->OSPEEDR |= 0x01;
	
	// set I/O no pull-up pull-down
	// 00 = no pull-up, no pull-down(default),
	// 01 = pull-up, 10 = pull down, 11 = reserved
	GPIOB->PUPDR &= ~(0x03<<(2*6));
	GPIOB->PUPDR &= ~(0x03<<(2*7));
	// set i/o la no pull-up pull-down
	// no pull-up/pull-down (00, default)
	//
	GPIOA->PUPDR &= ~(0x03);
}

int main(void){
	GPIO_Clock_Enable();	//cap xung nhip
	GPIO_Pin_Init();	//khoi tao cac pin 6,7 
	Systick_init(2097000);	// load value systick load = xung nhip chip
	GPIOB->ODR |= 1<<6; //light on
	GPIOB->ODR |= 1<<7;	// light on
	
	
	while(1) {; // Cho no loop vo cuc (dead loop, program hang there :)) )
				//Systick_init(2070000);
				//SysTick_Handler();
				//Delay(1000);
				//GPIOB->ODR ^= 1<<6;	//light switch
				//GPIOB->ODR ^= 1<<7;	//light switch
}
}


