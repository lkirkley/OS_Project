// BROKEN CODE

#include <stdlib.h>
#include <stdio.h>

void proc_gen(int n)
{
	FILE* fp;
	char s[32];
	int prior;
	for(int i=0;i<n;i++)
	{
		prior = i%4;
		sprintf(s,"n%i",i);
		fp = fopen(s,"w");
		if(!fp)
			dam("file did not open");
		fprintf(fp,"%9i\n",prior);                // Priority of the file
        fprintf(fp,"%9i\n",0);                                  // Position in the file
        fprintf(fp,"%9i\n",1000);                               // Memory of the file
        fprintf(fp,"%9i\n",5000);                               // Remain
        fprintf(fp,"%9i\n",0);                                  // Start time
        fprintf(fp,"%9i\n",0);                                  // End time
		
		for(int i=0;i<100;i++)
		{
			fprintf(fp,"%3i\n",i);
		}
	}
}
int main()
{
	proc_gen(10);
}