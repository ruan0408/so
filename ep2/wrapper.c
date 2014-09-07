/*isso vai em /usr/include/chpriority.h*/
#include <lib.h>
#include <unistd.h>

PUBLIC int chpriority(int pid, int priority)/*parametros para a sua syscall vão aqui*/
{
	message m;
	m.m1_i1 = pid;
	m.m1_i2 = priority;
	return(_syscall(MM, CHPRIORITY, &m));
}