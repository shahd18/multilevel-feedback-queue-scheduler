/*
  SHAHD ALI ALSHIKHI 2111228
  
  SHAHAD AHMED ALQARNI 2111214

*/

#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 100
#define QUANTUM1 8
#define QUANTUM2 16

//processes struct to hold information of each process
typedef struct Process {
  int responseTime;
  int turnArountTime;
  int BurstTime;
  int waitingTime;
  char Q[3];
} Process;

//first round robin queue Q0
//the queue will let the process enter queue for 8ms
void RR1(Process *a, int length, int *timer) { //timer to keep track of process
  for (int i = 0; i < length; i++) {
    a[i].responseTime = *timer; //response to process request
    if (a[i].BurstTime <= QUANTUM1) { //check brust time if it less than or equal to the queue quantum 8
      *timer += a[i].BurstTime;
      a[i].turnArountTime = *timer; //arrival time is zero so the turnaround time will equal timer
      a[i].BurstTime = 0;
      strcpy(a[i].Q, "Q0"); //demonstrate in which queue the process finished
      continue;
    }
    //if brust is greater than the queue quantum 8
    a[i].BurstTime -= QUANTUM1; //decrease brust time by the quantum of the first queue
    *timer += QUANTUM1; //increase timer by quantum of the first queue 8
  }
}


//second round robin queue Q1
//the queue will let the process enter queue for 16ms
void RR2(Process *a, int length, int *timer) {
  for (int i = 0; i < length; i++) {
    if (a[i].BurstTime == 0) continue; // check if the process has reminaning brust time if not then the proccess finished continue 
    if (a[i].BurstTime <= QUANTUM2) { // check if the brust time is less than or equal to the queue quantum 16
      *timer += a[i].BurstTime; //increase timer by brust time of the process
      a[i].turnArountTime = *timer; //the turnaround time of the process will equal timer
      a[i].BurstTime = 0; //the process done exceuting so the brust will be zero
      strcpy(a[i].Q, "Q1"); //demonstrate in which queue the process finished
      continue; //continue to another process
    }
    a[i].BurstTime -= QUANTUM2; //if the brust is not less than or equal to the queue quantum 16 decrease brust time 
    *timer += QUANTUM2; //increasse timer for the process by  quantum of the second queue 16
  }
}


//third queue Q2 first come first serve 
//the queue will exceute the riminaning processes
void FCFS(Process *a, int length, int *timer) {
  for (int i = 0; i < length; i++) {
    if (a[i].BurstTime == 0) continue; //if the process finished continue to the next
    *timer += a[i].BurstTime; //increase timer by the remining brust time for the process 
    a[i].BurstTime = 0;//the process done exceuting so the brust will be zero
    a[i].turnArountTime = *timer; //the turnaround time of the process will equal timer
    strcpy(a[i].Q, "Q2"); //demonstrate in which queue the process finished
  }
}



// display the processes and their information
void printProcesses(Process *processes, int length, int bursttime[MAX_PROCESSES]) {
  printf("\n\t--------------------------------Scheduling Table---------------------------------\n\n");
  printf("\tProcess ID | Burst Time    | Response Time    | Turnaround Time |   Waiting Time    | Queue\n");
  int total_waiting_time = 0;
  for (int i = 0; i < length; i++) {
    processes[i].waitingTime = processes[i].turnArountTime - bursttime[i]; //calculate waiting time of each process
    total_waiting_time += processes[i].waitingTime;
    printf("\t%d\t   | \t%d\t   | \t%d\t      | \t%d\t| \t%d\t    |\t%s\n", i + 1,bursttime[i], processes[i].responseTime, processes[i].turnArountTime, processes[i].waitingTime,  processes[i].Q);
}
printf("\n..Average waiting time: %.2f\n", (float)total_waiting_time / length); //calculate avarege waiting time of all processes
}



//main method
int main() {
  int bursttime[MAX_PROCESSES]; //array of processes brust time
  int process_count; //number of processess
  int timer = 0; //keep track

  printf("Enter the number of processes: ");
  scanf("%d", &process_count);

  Process processes[process_count]; //set processes array size initilaized by user
  memset(processes, 0, sizeof(processes)); //in memory initilaze the array of processes to zero

  printf("Enter the burst time of each process: \n");
  for (int i = 0; i < process_count; i++) {
    printf("P[%d]: ", i + 1);
    scanf("%d", &bursttime[i]); //save brust times entered byy user in an array
    processes[i].BurstTime = bursttime[i]; //initilize processec brust time to the array of brust time
  }
  
  
    RR1(processes, process_count, &timer);
    RR2(processes, process_count, &timer);
    FCFS(processes, process_count, &timer);
  
  //display result
  printProcesses(processes, process_count, bursttime);
  
  //find processes Throughput and total time of exceution
  int total_burst_time = 0;
  int Throughput = 0;
  for (int i = 0; i < process_count; i++) {
    total_burst_time += bursttime[i];
    Throughput+=processes[i].turnArountTime;
  }

  printf("..Total time taken: %d\n", timer);
  printf("..Throughput: %.2f\n", (float)Throughput/process_count);

  return 0;
}