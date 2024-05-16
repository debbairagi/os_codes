#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int remainingTime; // To track remaining burst time in SJF
};

void findWaitingTime(Process proc[], int n)
{
    int complete = 0, currentTime = 0, shortest = 0, finish_time;
    bool check = false;
    // Loop until all processes are completed
    while (complete != n)
    {
        // Find the shortest remaining time process among the arrived processes
        shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if ((proc[i].arrivalTime <= currentTime) &&
                (proc[i].remainingTime < proc[shortest].remainingTime || shortest == -1) &&
                proc[i].remainingTime > 0)
            {
                shortest = i;
                check = true;
            }
        }
        if (check == false)
        { // No process available at this time
            currentTime++;
            continue;
        }
        // Execute the shortest process
        proc[shortest].remainingTime--;

        // If the process completes, update its completion time and other metrics
        if (proc[shortest].remainingTime == 0)
        {
            complete++;
            finish_time = currentTime + 1; // Since we're incrementing after execution
            proc[shortest].completionTime = finish_time;
            proc[shortest].turnaroundTime = finish_time - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        }
        currentTime++;
    }
}

void findTurnaroundTime(Process proc[], int n)
{
    // Turnaround time already calculated in findWaitingTime
}

void findCompletionTime(Process proc[], int n)
{
    // Completion time already calculated in findWaitingTime
}

void findSJF(Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        proc[i].remainingTime = proc[i].burstTime; // Initialize remaining time
    }
    findWaitingTime(proc, n);
}

void printSJF(Process proc[], int n)
{
    cout << "SJF Scheduling:" << endl;
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround "
            "Time\tWaiting Time"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << proc[i].pid << "\t" << proc[i].arrivalTime << "\t\t"
             << proc[i].burstTime << "\t\t" << proc[i].completionTime << "\t\t"
             << proc[i].turnaroundTime << "\t\t" << proc[i].waitingTime << endl;
    }
}

int main()
{
    int n = 5;
    Process proc[5] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 2}, {4, 3, 4}, {5, 4, 1}};
    findSJF(proc, n);
    printSJF(proc, n);

    return 0;
}
