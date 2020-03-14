/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "doggos.h"
#include "serial_tty.h"
#include <stdio.h>
			
void context_switch(char**, char**);
void resume(int);

int pidA;
int pidB;

void nibA() {
  //printf("In funcA, before doing stuff\n");
  //int a = 90;
  //for(int i = 0; i < 10; i++) a++;
  //a should be 100 at this point
  context_switch(&(process_table[pidA].prstackptr), &(process_table[pidB].prstackptr));

  printf("We're back from running nibB!\n");
  //if(a == 100) printf("Yay~ a is the right value\n");
  //else printf("Nuu~ a is wrong value :(\n");
  while(1); //block, until scheduler is implemented
}

void nibB() {
  printf("Reached funcB, from A, going to return\n");
  context_switch(&(process_table[pidB].prstackptr), &(process_table[pidA].prstackptr));
}


int main(void) {
  configure_serial_comm();
  pidA = create(nibA, "nibba", 1);
  pidB = create(nibB, "nibb", 1);
  printf("created the two things\n");
  resume(pidA);
}

void resume(int pid) {
  context_switch(&(process_table[7].prstackptr), &(process_table[pid].prstackptr));
}
