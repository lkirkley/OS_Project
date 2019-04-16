#include <stdio.h>
#include <stdio.h>
#include "utils.h"
#include "math.h"

static FILE *fp;
static int position;
static int remain;
static int number_of_process;
void proc_open(int n)
{
        char s[32];
        sprintf(s,"p%i",n);
        fp= fopen(s,"r+");
        if(!fp)
                dam("file did not open");
        fseek(fp,10,0);
        fscanf(fp, "%i", &position);
        fseek(fp,30,0);
        fscanf(fp,"%i",&remain);
        fseek(fp,60,0);
        fscanf(fp,"%i",&number_of_process);
}
void proc_close()                                               
{
        fseek(fp,10,0);
        fprintf(fp,"%9i",position);
        fseek(fp,30,0);
        fprintf(fp,"%9i",remain);
        fclose(fp);
}
int proc_exe(int n, int quant)
{
        int count = 0;
        int i=0;
        int x;
        proc_open(n);                                           // Opens current file
        fseek(fp, 70 + (position << 2),0);                      //60 for s.time and e.time
        for(;;)
        {
                if(fscanf(fp,"%i",&x) == EOF)
                {
                        //printf("END OF FILE: %i\n",n);
                        remain -= count;
                        count |= 1<< 29;
                        break;
                }

                count += x;
                ++position;
                if(count > remain)
                {
                        remain -= count;
                        count |=  1<<28;
                        break;
                }
                if(count > quant)
                {
                        remain -= count;
                        count |= 1<<30;
                        break;
                }
                if(++i>20) //                                                  DELETE
                {
                        remain = remain - count;
                        break;
                }

        }
        proc_close();
        return count;
}
int get_priority(int n)
{
        int x;
        proc_open(n);
        fseek(fp,0,0);
        fscanf(fp,"%i",&x);
        proc_close();
        return x;
}
/* Setting up the queue for the process based on priority, block, and inial starting conditions */
/*
        Queues: 0 = priority 0  highest
                1 = priority 1
                2 = priority 2
                3 = priority 3  lowest
                4 = blocked process
                5 = blocked time
                6 = intial unsorted processes
                7 = average runtime for priority 0
                8 = avg runtime for priority 1
                9 = avg runtime for priority 2
                10 = avg runtime for priority 3
*/

int qs[11][1<<20];
int ts[11] = {0,0,0,0,0,0,0,0,0,0,0};

void enq(int q, int n)
{
        qs[q][ts[q]++] = n;
        return;
}
void deq(int q, int p)
{
        qs[q][p] = qs[q][--ts[q]];
}

/* Functions for time */

void set_start(int n, int start)
{
        int temp;
        proc_open(n);
        fseek(fp, 40, 0);
        fprintf(fp, "%9i", start);
        fseek(fp, 40, 0);
        fscanf(fp,"%i",&temp);
        //printf("Start Time : %i %i\n",temp,n);
        proc_close();
}
void set_end(int n, int end)
{
        int temp;
        proc_open(n);
        fseek(fp, 50, 0);
        fprintf(fp, "%9i", end);
        fseek(fp, 50, 0);
        fscanf(fp,"%i",&temp);
        //printf("End Time : %i %i\n",temp,n);
        proc_close();
}

int timeTaken(int n)
{
        int end;
        int start;
        int time_taken;
        proc_open(n);
        fseek(fp,40,0);
        fscanf(fp, "%i", &start);
        fseek(fp,50,0);
        fscanf(fp, "%i", &end);
        time_taken= end - start;
        proc_close();
        return time_taken;
}
/*
void average()
{
        int avg0=0, avg1=0, avg2=0, avg3=0;
        for(int i = 0; i< ts[7];i++)
        {
                avg0 += qs[7][i];
        }
        avg0 = avg0 / ts[7];
        for(int i = 0; i< ts[8];i++)
        {
                avg1 += qs[8][i];
        }
        avg1 = avg1 / ts[8];
        for(int i = 0; i< ts[9];i++)
        {
                avg2 += qs[9][i];
        }
        avg2 = avg2 / ts[9];
        for(int i = 0; i< ts[10];i++)
        {
                avg3 += qs[10][i];
        }
        avg3 = avg3 / ts[10];

        int std0=0, std1=0, std2=0, std3=0;
        for(int i = 0; i< ts[7];i++)
        {
                std0 += ((i-avg0)*(i-avg0));
        }
        std0 /= ts[7];
        std0 = sqrt(std0);
        for(int i = 0; i< ts[8];i++)
        {
                std1 += ((i-avg1)*(i-avg1));
        }
        std1 /= ts[8];
        std1 = sqrt(std1);
        for(int i = 0; i< ts[9];i++)
        {
                std2 += ((i-avg2)*(i-avg2));
        }
        std2 /= ts[9];
        std2 = sqrt(std2);
        for(int i = 0; i< ts[10];i++)
        {
                std3 += ((i-avg3)*(i-avg3));
        }
        std3 /= ts[10];
        std3 = sqrt(std3);
        
        printf("Priority: 0\n Average Time: %i\n Standard Dev: %i\n",avg0,std0);
        printf("Priority: 1\n Average Time: %i\n Standard Dev: %i\n",avg1,std1);
        printf("Priority: 2\n Average Time: %i\n Standard Dev: %i\n",avg2,std2);
        printf("Priority: 3\n Average Time: %i\n Standard Dev: %i\n",avg3,std3);
}
*/
/* Scheduler execution */

void sched()
{
        int x;
        int time =0;
        int priority;
        int entryTime = random_between(400, 40000);
        int run =0;
        int avg =0;

    for(;;)
    {
        for(int i=0; i<4; i++)                                                  //(RUNS EACH PRIORITY QUEUE, FIX ME)
        {
            for(int bq = 0; bq< ts[4]; bq++)
            {
                if(qs[5][bq] <= time)                           // That block process is ready                    DELETE
                {
//                  printf("UNBLOCKING %i\n", qs[4][bq]);
                    priority = get_priority(qs[4][bq]);
                    enq(priority, qs[4][bq]);
                    deq(4,bq);
                    deq(5,bq);
                    bq--;
                }
            }
           if(entryTime <= time && ts[6] !=0)                      // Add process to it queue
            {
                priority = get_priority(qs[6][0]);
                set_start(qs[6][0],time);
                enq(priority, qs[6][0]);
                deq(6,0);
                entryTime += random_between(400,4000);
            }
            for(int j=0; j<ts[i]; j++)                              // Goes throught each process part of the current queue
            {
                if(ts[i] == 0)                                  
                {
                    break;
                }
                x = proc_exe(qs[i][j],1000);
                if(x & (1 << 30))
                {
//                  printf("Qunatum Reached: %i, %i Nothing Happens\n",i,qs[i][j]);
                }
                else if(x & (1 << 29))
                {
//                  printf("Time Alloted Reached: %i, %i Process Deleted\n",i,qs[i][j]);
                    set_end(qs[i][j],time);
                    avg = timeTaken(qs[i][j]);
                    /*
                    if(i==0)
                        enq(7,avg);
                    if(i==1)
                        enq(8,avg);                                 DELETE
                    if(i==2)
                        enq(9,avg);
                    if(i==3)
                        enq(10,avg);
                    deq(i,j);*/ 
                    j--;
                }
                else if(x & (1 << 28))
                {
//                      printf("Proces Finished\n");
                        set_end(qs[i][j],time);
                        avg = timeTaken(qs[i][j]);
                        /*
                        if(i==0)
                                enq(7,avg);
                        if(i==1)
                                enq(8,avg);                                DELETE
                        if(i==2)
                                 enq(9,avg);
                        if(i==3)
                                    enq(10,avg);
                        deq(i,j);
                        */
                        j--;
                }
                else
                {
//                      printf("Process Blocked: %i %i\n",i,qs[i][j]);
                        int random_t = random_between(4,100);
                        enq(4,qs[i][j]);
                        enq(5,random_t + time);
                        deq(i,j);
                        j--;
                }
                        x &= 0x0ffffff;
                        time += x;
                }
        }
                if(ts[0] == 0 && ts[1] == 0 && ts[2] == 0 && ts[3] == 0 && ts[4] != 0 && ts[6] == 0)
                {
//                      printf("Everything is blocked\n");
                       time = qs[5][0];
                }
                else if(ts[0] == 0 && ts[1] == 0 && ts[2] == 0 && ts[3] == 0 && ts[4] == 0 && ts[6] !=0)
                {
//                      printf("Adding a process\n");
                        time = entryTime;
                }
                else if(ts[0] == 0 && ts[1] == 0 && ts[2] == 0 && ts[3] == 0 && ts[4] != 0 && ts[6] != 0)
                {
//                      printf("No process ready\n");
                        if(entryTime < qs[5][0])
                                time = qs[5][0];
                        else
                                time = entryTime;
                }
                else if(ts[0] == 0 && ts[1] == 0 && ts[2] == 0 && ts[3] == 0 && ts[4] == 0 && ts[6] == 0)
                {
                        printf("DONE\n");
                        average();
                        break;
                }
                run++;
        }
}
/* Intial process queue */

void load_proc(int n)                           // Puts every process into a single queue to be sorted when added, works
{
    for(int i=0; i<n; i++)
    {
        enq(6,i);
    }
    sched();
    return;
}

int main()
{
    proc_open(0);
    printf("Random number of process :%i\n", number_of_process);
    printf("Begin Scheduler\n");
    load_proc(number_of_process);
}