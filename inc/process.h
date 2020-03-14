#include <stdint.h>

typedef enum priorities {
  READY = 0,    //Can contend to run, but isn't
  ASLEEP = 2,   //Cannot contend to run
  RUNNING = 3,  //Is running
} priority;

typedef struct proc_t {
  char* prstackptr;
  char* prlinkreg;
  uint16_t pid;
  char* pname;
  uint16_t priority;
  void (*func_ptr)(void);

  priority prstate;
  //might need stack size
} process_t;

process_t process_table[8];  //introduce the process table, 8 entries only

uint16_t create(void (*func_ptr)(void), char* name, uint16_t priority);
