#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Run your simulator for following inputs
Part 1:

    Process     Arrival Time     Service Time       Start Time      Finish Time     Wait Time       Turnaround Time
    A           0                3                  *               *               *               *
    B           2                6                  *               *               *               *
    C           4                4                  *               *               *               *
    D           6                5                  *               *               *               *
    E           8                2                  *               *               *               *

Part 2:
   Process     Arrival Time     Service Time       Start Time      Finish Time     Wait Time       Turnaround Time
    A           0                8                  *               *               *               *
    B           1                5                  *               *               *               *
    C           2                9                  *               *               *               *
    D           3                2                  *               *               *               *
    E           4                6                  *               *               *               *
*/

/*
To Do:
    - Parse input file and store process' name, arrival time, and service time to own struct
*/
struct Process {
    // struct for each process
    char name[2];
    int arr_time;
    int serv_time;
};

void parser(struct Process *inp) {
    FILE *fp1;
    int lineP;
    char *rch;
    char str[20];
    int temp;
    int process_ind = 0;
    fp1 = fopen("part2.txt", "r"); 
    while (fgets(str, sizeof(str), fp1) != NULL)
	{
		lineP = 0;
		rch = strtok(str, " ");					// use strtok to break up the line by : or . or ; This would separate each line into the different events
		while (rch != NULL)
		{
			switch (lineP)
            {
            case 0:
                strcpy(inp[process_ind].name, rch);
                break;            
            case 1:
                temp = atoi(rch);
                inp[process_ind].arr_time = temp;
                break;
            case 2:
                temp = atoi(rch);
                inp[process_ind].serv_time = temp;
                break;
            }			
			lineP++;								//keep track of how many events are in that line
            rch = strtok(NULL, " ");				//needed for strtok to continue in the while loop
		}
        process_ind++;
    }
}

void FCFS(struct Process *inp){
    /*
    Algorithm for First Come First Serve
    */
}

void SPN(struct Process *inp){
    /*
    Algorithm for Shortest Process Next
    */
}

void SRT(struct Process *inp){
    /*
    Algorithm for Shortest-Remaining Time
    */
}
int main() {
    struct Process inp[5];
    // parse input file and store input to process struct
    parser(inp);
    
    printf("%s\n", inp[0].name);
    printf("%d\n", inp[0].arr_time);
    printf("%d\n", inp[0].serv_time);
    
    return 0;
}