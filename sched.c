include <stdio.h>
#include <stdlib.h>
#include "Process.h"


#define totalProcess 10



Process* AllTheProcess[totalProcess];           // Unsorted Process array
Process* PriorityQs[4][totalProcess];           // Priority sorted array
Process* BlockQueue[totalProcess];
Process* ReadyQueue[totalProcess];
int tailIndex[6] = {0};                         // 1-4 Priority Queues, 5 Blocked, 6 Ready

void generateProcessess(void) {
    for (int i = 0; i < totalProcess; i++) {
        AllTheProcess[i] = createProcess();
    }
    return;
}

void putProcessintoPQ(void) {
    for (int i = 0; i < totalProcess; i++) {
        InstBlock * instB = getInstBlock(AllTheProcess[i]);
        if (getPriority(instB) == 0) {
            PriorityQs[0][tailIndex[0]++] = AllTheProcess[i];
        }
        else if (getPriority(instB) == 1) {
            PriorityQs[1][tailIndex[1]++] = AllTheProcess[i];
        }
        else if (getPriority(instB) == 2) {
            PriorityQs[2][tailIndex[2]++] = AllTheProcess[i];
        }
        else {
            PriorityQs[3][tailIndex[3]++] = AllTheProcess[i];
        }
        }

    return;
    }
void enq()
{
        //AllTheProcess[totalProcesses++] = ;
}
void deq(Process * proc)
{
 
}

void process_handler()
{
    int input[3] = {0,0,0};
    int scheduler_time = 0;
    while(input[0] != -1 || input[1] != -1 || input[2] != -1)          //Infinite Loop unless we are done, then we are going to stahp everything, so we are checking that these values are not -1, and if they are, we blow this popsicle stand and get some suckers.
    {
        while(input[0] != -9 || input[1] != -9 || input[2] != -9)                         // FIFO LOOP
        {
            // CHECK IF THE FIRST THING READ IS (-1,-1,-1)
            if(input[0] == -1 || input[1] == -1 || input[2] == -1){
                return;
            }
            // BLOCK QUEUE CHECK
            for(int i = 0; i<BlockQueue[tailIndex[5]]; i++)
            {
                if(input[3] == processNumber)
                {
                    // UPDATE BLOCKQUEUE TIME
                        BlockQueue[tailIndex[i]] == getMS();
                    // ENQ INTO READY
                        ReadyQueue[tailIndex[i]++] = totalProcesses;
                    // DEQ FROM BLOCK
                        ReadyQueue[tailIndex[i]] = BlockQueue[tailIndex[i]--];
                }
            }
            // READY QUEUE CHECK
            for(int i = 0; i<ReadyQueue[tailIndex[6]]; i++)
            {
                if(time_requested<=ms)
                {
                    // GET THE PROCESS'S PRIORITY
                        ReadyQueue[tailIndex[i]] = getPriority();

                   // ENQ INTO RESPECTED PRIORITY
                        if (getPriority() == 0) {
                        ReadyQueue[tailIndex[i++] = PriorityQs[0][tailIndex[0]];
                        }
                         else if (getPriority() == 1) {
                        ReadyQueue[tailIndex[i++] = PriorityQs[1][tailIndex[1]];
                        }
                         else if (getPriority() == 2) {
                        ReadyQueue[tailIndex[i++] = PriorityQs[2][tailIndex[2]];
                        }        
                       else if (getPriority() == 3) {
                        ReadyQueue[tailIndex[i++] = PriorityQs[3][tailIndex[3]];
                        }
                    // DEQ FROM READY
                        PriorityQs[][tailIndex[]--] = ReadyQueue[tailIndex[i]];
                        }
            }
        }
        //Priority based for loop
        for(int i=0; i<3; i++)
        {
                //PROCESS TILL YOU BLOCK IT
        }
        // CHECK IF EVERYTHING HAS BEEN PROCESSED
        if(PriorityQs[0][0] == NULL && PriorityQs[1][0] == NULL && PriorityQs[2][0] == NULL && PriorityQs[3][0] == NULL && BlockQueue[0] == NULL && ReadyQueue[0] == NULL)
        {
                // SEND TO DISK THE END OF COMMUNITICATION CODE
                printf("-1 -1 -1\n");
                // I would end communtations here however, the FIFO is in write mode. So, I am going to the break cases end communication.
                        break;
                    }

        // PRINT FIFO CODE FOR SWITCH DISK TO SWITCH FROM READING TO WRITING
                print("-9 -9 -9\n");
        // Close FIFO
                close(fd);
        // OPEN FIFO FOR READING
                fd = open(myfifo, O_RDONLY);
        // RANDOMLY UPDATE SCHEDULER TIME (1-10 depends on the group)

        }

}

void process_stats()
{


}

int main()
{

    return 0;
}
