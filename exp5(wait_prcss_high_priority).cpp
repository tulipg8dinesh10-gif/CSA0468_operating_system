#include <stdio.h>

struct priority_scheduling { 
    char process_name; 
    int burst_time; 
    int waiting_time; 
    int turn_around_time; 
    int priority; 
}; 

int main() { 
    int number_of_process; 
    int total = 0; 
    struct priority_scheduling temp_process; 
    int ASCII_number = 65; // 65 is ASCII for 'A'
    int position; 
    float average_waiting_time; 
    float average_turnaround_time; 

    // 1. Get number of processes
    printf("Enter the total number of Processes: "); 
    scanf("%d", &number_of_process); 
    
    struct priority_scheduling process[number_of_process]; 

    // 2. Input details for each process
    printf("\nPlease Enter the Burst Time and Priority of each process:\n"); 
    for (int i = 0; i < number_of_process; i++) { 
        process[i].process_name = (char) ASCII_number; 
        printf("\nEnter the details of process %c:\n", process[i].process_name); 
        
        printf("Enter the burst time: "); 
        scanf("%d", &process[i].burst_time); 
        
        printf("Enter the priority: "); 
        scanf("%d", &process[i].priority); 
        
        ASCII_number++; 
    } 

    // 3. Sort processes by priority (Highest Priority First)
    for (int i = 0; i < number_of_process; i++) { 
        position = i; 
        for (int j = i + 1; j < number_of_process; j++) { 
            if (process[j].priority > process[position].priority) {
                position = j; 
            }
        } 
        temp_process = process[i]; 
        process[i] = process[position]; 
        process[position] = temp_process; 
    } 

    // 4. Calculate Waiting Time (WT)
    process[0].waiting_time = 0; 
    for (int i = 1; i < number_of_process; i++) { 
        process[i].waiting_time = 0; 
        for (int j = 0; j < i; j++) { 
            process[i].waiting_time += process[j].burst_time; 
        } 
        total += process[i].waiting_time; 
    } 

    // Calculate Average Waiting Time
    average_waiting_time = (float) total / (float) number_of_process; 
    
    // Reset total to calculate Turnaround Time sum
    total = 0; 

    // 5. Print Table Headings
    printf("\n\nProcess_name \t Burst Time \t Waiting Time \t Turnaround Time\n"); 
    printf("-----------------------------------------------------------------\n"); 

    // 6. Calculate Turnaround Time (TAT) and Print Rows
    for (int i = 0; i < number_of_process; i++) { 
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time; 
        total += process[i].turn_around_time; // Accumulate total TAT
        
        printf("\t %c \t\t %d \t\t %d \t\t %d\n", 
               process[i].process_name, 
               process[i].burst_time, 
               process[i].waiting_time, 
               process[i].turn_around_time); 
    } 
    printf("-----------------------------------------------------------------\n"); 

    // 7. Calculate and display averages
    average_turnaround_time = (float) total / (float) number_of_process; 
    
    printf("\n\nAverage Waiting Time : %f", average_waiting_time); 
    printf("\nAverage Turnaround Time: %f\n", average_turnaround_time); 

    return 0;
}
