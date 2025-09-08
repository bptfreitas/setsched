#ifndef __CPU_STRESS_H__

#define __CPU_STRESS_H__

void func_sched_fifo( int id, int prio, void (*foo)(int) );


void CPU_intensive( long int max );

#endif