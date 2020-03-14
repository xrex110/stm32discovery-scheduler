#include "doggos.h"

//create - create and initialize a process
uint16_t create(void (*func_ptr)(void), char* name, uint16_t priority) {
  static uint8_t nextpid = 0;
  static int* magical_stack = 0x20001BDC;
  process_t* newproc = &process_table[nextpid];
  newproc->pid = nextpid;
  newproc->pname = name;
  newproc->priority = priority;
  newproc->func_ptr = func_ptr;
  newproc->prstate = READY;

  //char* stack_ptr;
  //asm volatile("mov %0, sp\n"
  //             : "=r"(stack_ptr));

  *--magical_stack = (int) func_ptr;
  *--magical_stack = 0;
  *--magical_stack = 0;
  *--magical_stack = 0;
  *--magical_stack = 0;

  //Gotta setup the stacc for this function
  //not sure if I should be doing it right here tho
  //asm volatile("sub sp, #4\n"
  //             "mov r0, %0\n"
  //             "ldr r0, [sp]\n"
  //             "sub sp, #16\n"
  //             : :"r"(func_ptr) : "r0", "cc");

  newproc->prstackptr = magical_stack;

  magical_stack -= 256;

  return nextpid++;
}
