#include <stdio.h> 

int main() 
{ 
    int at[10], bt[10], pr[10]; 
    int n, i, j, temp, time = 0, count, over = 0, sum_wait = 0, sum_turnaround = 0, start; 
    float avgwait, avgturn; 

    printf("Enter the number of processes: "); 
    scanf("%d", &n); 

    for(i = 0; i < n; i++) 
    { 
        printf("Enter the arrival time and execution (burst) time for process %d: ", i + 1); 
        // FIXED: Inside the loop body now
        scanf("%d%d", &at[i], &bt[i]); 
        pr[i] = i + 1; 
    } 
    // Sort processes initially by Arrival Time
    for(i = 0; i < n - 1; i++) 
    { 
        for(j = i + 1; j < n; j++) 
        { 
            if(at[i] > at[j]) 
            { 
                temp = at[i]; at[i] = at[j]; at[j] = temp; 
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp; 
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp; 
            } 
        } 
    } 
    // FIXED: Cleaned up print header formatting to align with the data columns
    printf("\n\nProcess\t| Arrival\t| Burst\t| Start\t| End\t| Waiting\t| Turnaround\n");
    printf("-----------------------------------------------------------------------------------\n");
    while(over < n) 
    { 
        count = 0; 
        // FIXED: Removed accidental empty braces. This correctly checks how many jobs have arrived.
        for(i = over; i < n; i++) 
        { 
            if(at[i] <= time) 
                count++; 
            else 
                break; 
        } 
        // If no process has arrived yet, advance the time to the arrival time of the next process
        if(count == 0) 
        {
            time = at[over];
            continue;
        }
        // Sort the arrived processes by Burst Time (SJF logic)
        if(count > 1) 
        { 
            for(i = over; i < over + count - 1; i++) 
            { 
                for(j = i + 1; j < over + count; j++) 
                { 
                    if(bt[i] > bt[j]) 
                    { 
                        temp = at[i]; at[i] = at[j]; at[j] = temp; 
                        temp = bt[i]; bt[i] = bt[j]; bt[j] = temp; 
                        temp = pr[i]; pr[i] = pr[j]; pr[j] = temp; 
                    } 
                } 
            } 
        } 
        start = time; 
        time += bt[over]; 
        int turnaround_time = time - at[over];
        int waiting_time = turnaround_time - bt[over];
        // FIXED: Aligned output fields safely to match the header column mappings
        printf("p[%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n", 
               pr[over], at[over], bt[over], start, time, waiting_time, turnaround_time); 
        sum_wait += waiting_time; 
        sum_turnaround += turnaround_time; 
        over++; 
    } 
    avgwait = (float)sum_wait / (float)n; 
    avgturn = (float)sum_turnaround / (float)n; 
    printf("\nAverage waiting time is: %f\n", avgwait); 
    printf("Average turnaround time is: %f\n", avgturn); 

    return 0; 
}
