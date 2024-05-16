#include <iostream>
using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void findWaitingTime(Process proc[], int n)
{

    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++)
    {
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        if (proc[i].waiting_time < 0)
        {
            proc[i].waiting_time = 0;
        }
    }
}

void findTurnaroundTime(Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void findCompletionTime(Process proc[], int n)
{
    proc[0].completion_time = proc[0].burst_time;

    for (int i = 1; i < n; i++)
    {
        proc[i].completion_time = proc[i - 1].completion_time + proc[i].burst_time;
    }
}

void findFCFS(Process proc[], int n)
{
    findCompletionTime(proc, n);
    findTurnaroundTime(proc, n);
    findWaitingTime(proc, n);
}

void printFCFS(Process proc[], int n)
{
    cout << "FCFS Scheduling:" << endl;
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround "
            "Time\tWaiting Time"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << proc[i].pid << "\t" << proc[i].arrival_time << "\t\t"
             << proc[i].burst_time << "\t\t" << proc[i].completion_time << "\t\t"
             << proc[i].turnaround_time << "\t\t" << proc[i].waiting_time << endl;
    }
}

int main()
{
    int n = 5; // number of processes
    Process proc[5] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 2}, {4, 3, 4}, {5, 4, 1}};

    findFCFS(proc, n);
    printFCFS(proc, n);

    return 0;
}
