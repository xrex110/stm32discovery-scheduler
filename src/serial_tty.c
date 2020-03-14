#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#include "serial_tty.h"

#include <stdio.h>
#include <stdlib.h>

void configure_serial_comm() {
  //Enable RCC to USART1
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  RCC->APB2ENR |= RCC_APB2Periph_USART1;

  //Configure PA9 and PA10 for alternate function
  GPIOA->MODER &= ~(0x3c0000);
  GPIOA->MODER |= 0x280000;

  //Setup PA9 and PA10 alternate function to USART1_TX and USART1_RX respectively
  GPIOA->AFR[1] &= ~(0x00000ff0);
  GPIOA->AFR[1] |= 0x00000110;

  //Buffer allocation for stdin and stdout disabled
  setbuf(stdin, 0);
  setbuf(stdout, 0);

  USART1->CR1 &= ~(0x10009401);  //Disable USART for settings vals
  USART1->CR2 &= ~(0x3000);     //Clears stop

  USART1->BRR = 0x1a1; //0x1a1 = 417
  USART1->CR1 |= 0xd;

  while((USART1->ISR & 0x600000) != 0x600000);  //wait for USART setup
  return;
}

void __io_putchar(char c) {
  if(c == '\n') {   //If we try to write \n, write \r first
    while((USART1->ISR & 0x80) != 0x80);  //Wait to send data
    USART1->TDR = '\r';                    //send it
  }
  while((USART1->ISR & 0x80) != 0x80);  //Wait to send data
  USART1->TDR = c;                    //send it
}

char __io_getchar() {
  //Clear ORE in ISR
  if((USART1->ISR & 0x8) == 0x8) USART1->ICR &= ~(0x8);
  while((USART1->ISR & 0x20) != 0x20);

  //Now we actually read the stuff
  char c = USART1->RDR;
  if(c == '\r') c = '\n';
  __io_putchar(c);      //For echo'ing purposes
  return c;
}
