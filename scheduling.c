#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Instructions:
    Change the input file to the desired one using variable fp1 in parser
    Output desired algorithm with corresponding visual representation by uncommenting the code in main()
    
    Assumptions:
    The input file contains 5 processes
    There is a max total service time of 30 time units
    The first process starts at time 0
    No processes have the same start time
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
    int resume_time[10];
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

void FCFS(struct Process *inp, char* gantt){
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
            // print process data
            printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[i].name, inp[i].arr_time, inp[i].serv_time, inp[i].start_time, inp[i].fin_time, inp[i].wait_time, inp[i].turn_time);   
            // update gantt array
            for(int j=0; j<inp[0].fin_time; j++){
                gantt[j] = inp[0].name[0];
            }
            continue;
        }
        inp[i].start_time = temp_time;
        inp[i].fin_time = inp[i].start_time + inp[i].serv_time;
        inp[i].wait_time = inp[i].start_time - inp[i].arr_time;
        inp[i].turn_time = inp[i].fin_time - inp[i].arr_time;

        for(int j=temp_time; j<inp[i].fin_time; j++){
                gantt[j] = inp[i].name[0];
        }
        temp_time = inp[i].fin_time;

        printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[i].name, inp[i].arr_time, inp[i].serv_time, inp[i].start_time, inp[i].fin_time, inp[i].wait_time, inp[i].turn_time);   
   }
}

void SPN(struct Process *inp, char* gantt){
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
   for(int i=0; i<inp[0].fin_time; i++){
       gantt[i] = inp[0].name[0];
    }
   printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[0].name, inp[0].arr_time, inp[0].serv_time, inp[0].start_time, inp[0].fin_time, inp[0].wait_time, inp[0].turn_time);   
   ran_processes = ran_processes+1;
   // Fill in rest of processes information
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
           for(int i=temp_time; i<inp[temp_shortest_ind].fin_time; i++){
                gantt[i] = inp[temp_shortest_ind].name[0];
           }
           temp_time = inp[temp_shortest_ind].fin_time;
           printf("%s           %d                %d                  %d               %d               %d               %d\n", inp[temp_shortest_ind].name, inp[temp_shortest_ind].arr_time, inp[temp_shortest_ind].serv_time, inp[temp_shortest_ind].start_time, inp[temp_shortest_ind].fin_time, inp[temp_shortest_ind].wait_time, inp[temp_shortest_ind].turn_time);   
           
           ran_processes = ran_processes+1; // increment process ran counter
           flags[temp_shortest_ind-1]=1;    // flag ran process
           temp_shortest = 1000;            // reset shortest tracker
   }
   
}

void SRT(struct Process *inp, char* gantt){
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
    int gantt_ind = 0;
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
        // update gantt array / index
        gantt[gantt_ind] = inp[temp_shortest_ind].name[0];
        gantt_ind++;
        // update curr_time
        curr_time = curr_time + 1;
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
        
    }
}

void gantt(struct Process *inp, char *gantt){
    printf("Gantt Chart: \n");
    // Goes through gantt array and prints the visual presentation
    for(int i = 0; i<5; i++){
        for(int j = 0; j<30; j++){
            switch (i){
                case 0:
                    if(gantt[j]=='A'){
                        printf("A");
                    }
                    else{
                        printf(" ");
                    }
                    break;
                case 1:
                    if(gantt[j]=='B'){
                        printf("B");
                    }
                    else{
                        printf(" ");
                    }
                    break;
                case 2:
                    if(gantt[j]=='C'){
                        printf("C");
                    }
                    else{
                        printf(" ");
                    }
                    break;
                case 3:
                    if(gantt[j]=='D'){
                        printf("D");
                    }
                    else{
                        printf(" ");
                    }
                    break;
                case 4:
                    if(gantt[j]=='E'){
                        printf("E");
                    }
                    else{
                        printf(" ");
                    }
                    break;
            }
        }
        printf("\n");
    }
    
}

int main() {
    struct Process inp[5];
    // parse input file and store input to process struct
    parser(inp);
    printf("Process     Arrival Time     Service Time       Start Time      Finish Time     Wait Time       Turnaround Time\n");
    
    
    // Runs FCFS algorithm and prints the corresponding data table and gantt chart
    char gantt_fcfs[30];
    FCFS(inp, gantt_fcfs);
    gantt(inp, gantt_fcfs);
    

    /*
    // Runs SPN algorithm and prints the corresponding data table and gantt chart
    char gantt_spn[30];
    SPN(inp, gantt_spn);
    gantt(inp, gantt_spn);
    */

    /*
    // Runs SRT algorithm and prints the corresponding data table and gantt chart
    char gantt_srt[30];
    SRT(inp, gantt_srt);
    gantt(inp,gantt_srt);
    */

    return 0;
}