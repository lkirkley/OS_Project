#include <stdlib.h>
#include <stdio.h>

long q[10000];
int qi = 0;

FILE *fp;
FILE *f;

typedef struct {
    int loc : 30;
    int proc : 30;
} rec;

typedef union {
    rec x;
    long y;
} rec_un;

void inq(long n)
{
    q[qi++] = n;
}

long deq(int pos)
{
    long r = q[pos];
    q[pos] = q[--qi];
    return r;
}

void load_q(int time)
{
    static int t = -1;
    static rec_un x;
    int loc;
    int proc;

    if (t > time)
    {
        time = t;
    }

    while (t <= time)
    {
        if (t >= 0)
        {
            inq(x.y);
        }

        fscanf(fp, "%d %d %d\n", &t, &loc, &proc);
        x.x.loc = loc;
        x.x.proc = proc;
    } 
}

int smallest()
{
    int sp = 0;
    int i;
    
    for (i = 1; i < qi; i++)
    {
        if (q[i] < q[sp])
        {
            sp = i;
        }
    }
    return sp;
}

int largest()
{
    int yi= 0;
    int i;
    for (i = 1; i < qi; i++)
    {
        if (q[i] > q[yi])
        {
            yi = i;
        }
    }
    return yi;
}

int process(int time)
{
    static int dir = 0;

    if (dir == 0)
    {
        while (qi)
        {
            rec_un y;
            y.y = deq(smallest());
            time = time+5;
            fprintf(f, "%d %d\n", time, y.x.proc);
        }
    }
    else
    {
        while (qi)
        {
            rec_un y;
            y.y = deq(largest());
            time = time+5;
            fprintf(f, "%d  %d\n", time, y.x.proc);
        }
    }
    dir ^= 1;

    return time;
}


int main()
{
    int time = 0;

    fp = fopen("s_request.txt", "r");
    f = fopen("d_results.txt", "w");

    if (fp == NULL)
    {
        printf("Error: file could not open\n");
        exit(1);
    }

    fscanf(fp, "%3i", &time);
    fseek(fp, 0, 0);

    while (!feof(fp))
    {
        load_q(time);
        time = process(time);
    }

    fclose(fp);
    fclose(f);
}
