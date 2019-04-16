#include <stdio.h>
#include <stdlib.h>

static FILE *fp; 
static FILE *fp_out;

int qs[1<<20];
int ts = 0;

typedef struct 
{
	int loc  	:30;
	int proc 	:30;
}rec;

typedef union 
{
	rec 	x;
	long 	y;
}rec_un;	

// Simple Enque function
void enq(int n)
{
	int temp = ts;
    qs[ts++] = n;
	printf("%d\n",qs[temp]);
}
// Gets the information at the location being deleted, replaces the information with the last spot and returns the location
int deq(int pos)
{
    int r = qs[pos];
	qs[pos] = qs[--ts];
	return r;
}

// Used in conjuction with the direction of "needle"
int get_smallest()
{
	int smallest = qs[0];
	for(int i=1; i<ts; i++)
	{
		if(smallest > qs[i])
			smallest = qs[i];
	}
	return smallest;
}
int get_biggest()
{
	int biggest = qs[0];
	for(int i = 1; i<ts; i++)
	{
		if(biggest < qs[i])
			biggest = qs[i];
	}
	return biggest;
}
// Reads the information from the file and enqueues the location into the queue (What do you do with time requested and the process id) 
void load_requests(int time)
{
	int t;
	int loc;
	int proc;
	fscanf(fp,"%d%d%d",&t,&loc,&proc);
	printf("%d,%d,%d\n",t,loc,proc);
	enq(loc);
}
// Take the information in the queue and the direction of the head and write to another file
// What is written into the file is the updated time (+5 ms) and the location and process ID
void process_requests(int d)
{
	int spot;

	fp_out = fopen("p_data.txt","w");
	if(d%2 == 0)
	{
		spot = get_smallest();
	}
	else
	{
		spot = get_biggest();
	}
	
	fclose(fp_out);
}
int main()
{
	fp = fopen("data.txt","r");
	int time = 0;
	int count = 0;
	while(!feof(fp))
	{
		load_requests(time);
		process_requests(count);
		count++;
	}
	fclose(fp);
}
