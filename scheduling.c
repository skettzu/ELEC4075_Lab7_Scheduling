#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Run your simulator for following inputs
Part 1:
                                                                                    (start - arr)   (finish - arr)
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
    - Parse input file and store process' name, arrival time, and service time to own struct [Done]
    - Get FCFS working [Done]
    - Get SPN working [Done]
    - Get SRT working [Testing]
    - Get Table printing working [Testing]
    - Get Gantt Chart printing working
*/
struct Process {
    // struct for each process
    char name[2];
    int arr_time;
    int serv_time;
    int start_time;
    int fin_time;
    int wait_time;
    int turn_time;
};

void parser(struct Process *inp) {
    FILE *fp1;
    int lineP;
    char *rch;
    char str[20];
    int temp;
    int process_ind = 0;
    fp1 = fopen("part1.txt", "r"); 
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
   struct Process temp;
   
   // Re-order processes to be FCFS
   for (int i = 0; i<5; i++){
    if(i!=4){
        for (int j = i+1; j<5; j++){
            if (inp[i].start_time > inp[j].start_time){
                temp = inp[i];
                inp[i] = inp[j];
                inp[j] = temp;
            }
        }
    }
   }
   int temp_time;
   // Fill in rest of processes infomation
   for (int i = 0; i<5; i++){
        if(i==0){
            inp[0].start_time = inp[0].arr_time;
            inp[0].fin_time = inp[0].start_time + inp[0].serv_time;
            inp[0].wait_time = inp[0].start_time - inp[0].arr_time;
            inp[0].turn_time = inp[0].fin_time - inp[0].arr_time;
            temp_time = inp[0].fin_time;
            printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[i].name, inp[i].arr_time, inp[i].serv_time, inp[i].start_time, inp[i].fin_time, inp[i].wait_time, inp[i].turn_time);   
            continue;
        }
        inp[i].start_time = temp_time;
        inp[i].fin_time = inp[i].start_time + inp[i].serv_time;
        inp[i].wait_time = inp[i].start_time - inp[i].arr_time;
        inp[i].turn_time = inp[i].fin_time - inp[i].arr_time;
        temp_time = inp[i].fin_time;

        printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[i].name, inp[i].arr_time, inp[i].serv_time, inp[i].start_time, inp[i].fin_time, inp[i].wait_time, inp[i].turn_time);   
   }
}

void SPN(struct Process *inp){
    /*
    Algorithm for Shortest Process Next
    */
   struct Process temp;

   // Re-order processes to be FCFS
   for (int i = 0; i<5; i++){
    if(i!=4){
        for (int j = i+1; j<5; j++){
            if (inp[i].start_time > inp[j].start_time){
                temp = inp[i];
                inp[i] = inp[j];
                inp[j] = temp;
            }
        }
    }
   }
   int temp_time = 0;
   int ran_processes = 0;
   int flags[4] = {0,0,0,0};
   int temp_shortest = 1000;
   int temp_shortest_ind;
   // run first process
   inp[0].start_time = inp[0].arr_time;
   inp[0].fin_time = inp[0].start_time + inp[0].serv_time;
   inp[0].wait_time = inp[0].start_time - inp[0].arr_time;
   inp[0].turn_time = inp[0].fin_time - inp[0].arr_time;
   temp_time = inp[0].fin_time;
   printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[0].name, inp[0].arr_time, inp[0].serv_time, inp[0].start_time, inp[0].fin_time, inp[0].wait_time, inp[0].turn_time);   
   ran_processes = ran_processes+1;
   // Fill in rest of processes infomation
   while(ran_processes != 5){
        for(int i = 1; i < 5; i++){
            // check if ran
            if (flags[i-1]==1)
            {
                continue;
            }
            // check if arrived
            if(inp[i].arr_time<=temp_time){
                // keep track of shortest process time and index
                if (temp_shortest>inp[i].serv_time){
                    temp_shortest = inp[i].serv_time;
                    temp_shortest_ind = i;
                }
            }
        }
           // run process
           inp[temp_shortest_ind].start_time = temp_time;
           inp[temp_shortest_ind].fin_time = inp[temp_shortest_ind].start_time + inp[temp_shortest_ind].serv_time;
           inp[temp_shortest_ind].wait_time = inp[temp_shortest_ind].start_time - inp[temp_shortest_ind].arr_time;
           inp[temp_shortest_ind].turn_time = inp[temp_shortest_ind].fin_time - inp[temp_shortest_ind].arr_time;
           temp_time = inp[temp_shortest_ind].fin_time;
           printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[temp_shortest_ind].name, inp[temp_shortest_ind].arr_time, inp[temp_shortest_ind].serv_time, inp[temp_shortest_ind].start_time, inp[temp_shortest_ind].fin_time, inp[temp_shortest_ind].wait_time, inp[temp_shortest_ind].turn_time);   
           ran_processes = ran_processes+1; // increment process ran counter
           flags[temp_shortest_ind-1]=1;    // flag ran process
           temp_shortest = 1000;            // reset shortest tracker
   }
   
}

void SRT(struct Process *inp){
    /*
    Algorithm for Shortest-Remaining Time
    */

    // Keep track of current time
    int curr_time = 0;
    int tot_time = 0;
    int run_time[5] = {0,0,0,0,0};      // keep track of run time
    int flags[5] = {0,0,0,0,0};         // keep track if process ran
    int temp_serv_time[5] = {0,0,0,0,0};
    int temp_shortest = 1000;           // keep track of shortest process
    int temp_shortest_ind;              // keep track of shortest process index
    // find total service time and copy serv_time
    for(int i = 0; i < 5; i++){
        tot_time = tot_time + inp[i].serv_time;
        temp_serv_time[i] = inp[i].serv_time;
        inp[i].start_time = -1; // flag stating it hasn't been initialized
    }
    while(curr_time<tot_time){
        for(int i = 0; i < 5; i++){
            // check if ran
            if (flags[i]==1)
            {
                continue;
            }
            // check if arrived
            if(inp[i].arr_time<=curr_time){
                // keep track of shortest process time and index
                if (temp_shortest>temp_serv_time[i]){
                    temp_shortest = temp_serv_time[i];
                    temp_shortest_ind = i;
                }
            }
        }
        // run process for 1 time unit
        temp_serv_time[temp_shortest_ind] = temp_serv_time[temp_shortest_ind] - 1;
        // check if started before
        if (inp[temp_shortest_ind].start_time == -1){
            inp[temp_shortest_ind].start_time = curr_time;
        }
        //printf("%d", inp[temp_shortest_ind].start_time);
        //return;
        // check if finished running
        if (temp_serv_time[temp_shortest_ind] == 0){
            inp[temp_shortest_ind].fin_time = curr_time;
            flags[temp_shortest_ind] = 1;
            inp[temp_shortest_ind].wait_time = inp[temp_shortest_ind].start_time - inp[temp_shortest_ind].arr_time;
            inp[temp_shortest_ind].turn_time = inp[temp_shortest_ind].fin_time - inp[temp_shortest_ind].arr_time;
            printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[temp_shortest_ind].name, inp[temp_shortest_ind].arr_time, inp[temp_shortest_ind].serv_time, inp[temp_shortest_ind].start_time, inp[temp_shortest_ind].fin_time, inp[temp_shortest_ind].wait_time, inp[temp_shortest_ind].turn_time);   
        }
        // reset shortest time tracker
        temp_shortest = 1000;
        // update curr_time
        curr_time = curr_time + 1;
    }
}
int main() {
    struct Process inp[5];
    // parse input file and store input to process struct
    parser(inp);
    printf("Process     Arrival Time     Service Time       Start Time      Finish Time     Wait Time       Turnaround Time\n");
    //FCFS(inp);
    //SPN(inp);
    SRT(inp);
    //printf("%s\n", inp[0].name);
    //printf("%d\n", inp[0].arr_time);
    //printf("%d\n", inp[0].serv_time);
    
    return 0;
}