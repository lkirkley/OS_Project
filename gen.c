#include <stdio.h>
#include <stdlib.h>


// Returns Time and a Disk Block
// This is going to require actual time
int main()
{
	FILE *fp;
	fp = fopen("input_data.txt","w");
	int time = 0;
	for(int i = 0; i< 10; i++)
	{
		time += rand() %11;
		fprintf(fp,"%d %d %d\n", time, rand() % (1<<20), rand() % 100);
	}
	fclose(fp);
}
