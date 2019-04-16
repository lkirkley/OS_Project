//Provided by Titus
#include <stdlib.h>
#include <stdio.h>

FILE *f_in;
FILE *f_out;
int qs[10000];
int qi = 0;

typedef struct 
{
	unsigned int loc	:30;
	unsigned int proc	:30;
} rec;

typedef union 
{
	rec x;
	long y;
}rec_un;


int deq(int pos)
{
	long r = qs[pos];
	qs[pos] = qs[--qi];
	return r;
}

void enq(int n)
{
	qs[qi++]=n;
	return;
}

int get_biggest()
{
	int big = 0;
	
	for(int i = 1; i<qi; i++)
	{
		if(qs[big] < qs[i])
			big = i;
	}
	return big;
}

int get_smallest()
{
	int small = 0;
	for(int i = 1; i<qi; i++)
	{
		if(qs[small]>qs[i])
			small = i;
	}
	return small;
}

void load_q(int time) // time is in disk time
{
	static int t = -1;
	static rec_un x;
	int loc;
	int proc;
	
	if(t>time)
	{
		time = t;
	}
	while(t<= time)
	{
		if(t>=0)
		{
			enq(x.y);
		}
		fscanf(f_in,"%d %d %d\n",&t,&loc,&proc);
		x.x.loc = loc;
		x.x.proc = proc;
	}
	return;
}
int process(int time)
{
	static int dir = 0;

	if(dir)
	{
		while(qi)
		{
			rec_un y;
			y.y = deq(get_smallest());
			time += 5 ;
			fprintf(f_out,"%d %d\n", time, y.x.proc); //Returns the information to the file
		}
	}
	else 
	{
		while (qi)
		{
			rec_un y;
			y.y  = deq(get_biggest());
			time += 5;
			fprintf(f_out,"%d %d\n",time,y.x.proc);
		}
	}
	dir^=1;
	return time;
}

int main()
{
	f_in = fopen("s_request.txt","r");
	f_out = fopen("d_results.txt","w");

	long time = 0;
	while(!feof(f_in))
	{
		load_q(time);
		time = process(time);
	}
	
	fclose(f_in);
	fclose(f_out);
}