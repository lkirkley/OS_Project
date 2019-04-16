#include <stdlib.h>
#include <stdio.h>

int qs[10000];
int qi = 0;

typedef struct 
{
	loc		:30;
	proc	:30;
} rec;

typedef union 
{
	rec x;
	long x;
}rec_un;


{

}

int deq(int pos)
{
	int r = qs[pos];
	qs[pos] = qs[--qi];
	return r;
}

void enq(int n)
{
	qs[qi++]=n;
	return;
}

int load_q(int time) // time is in disk time
{
	int t;
	int loc;
	int proc;
	fscanf("%d%d%d\n",&t,&loc,&proc);
	enq(loc);
}

int main()
{
	while(!EOF)
	{
		// LOAD
		// PROCESS
	}	
}