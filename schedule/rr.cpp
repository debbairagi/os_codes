#include <iostream>
#include <queue>

using namespace std;

struct Process {
    int pid;       // Process ID
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int remainingTime; 
};

void findWaitingTime(Process proc[], int n, int quantum) {
    queue<int> readyQueue;
    int currentTime = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime; // Initialize remaining time
    }

    readyQueue.push(0); // Start with the first process

    while (completed != n) {
        int idx = readyQueue.front();
        readyQueue.pop();

        if (proc[idx].remainingTime <= quantum) {
            // Process completes within the time quantum
            currentTime += proc[idx].remainingTime;
            proc[idx].remainingTime = 0;
            proc[idx].completionTime = currentTime;
            proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
            completed++;
        } else {
            // Process partially executes within the time quantum
            currentTime += quantum;
            proc[idx].remainingTime -= quantum;
            readyQueue.push(idx); // Put the process back in the queue
        }

        // Check for newly arriving processes
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 &&
                find(readyQueue.begin(), readyQueue.end(), i) == readyQueue.end()) {
                readyQueue.push(i);
            }
        }
    }
}

// Calculate average turnaround and waiting times
void findAvgTime(Process proc[], int n, int quantum) {
    float total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(proc, n, quantum);

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + proc[i].waitingTime;
        total_tat = total_tat + proc[i].turnaroundTime;
    }

    cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
    cout << "Average turn around time = " << (float)total_tat / (float)n << endl;
}

// Function to calculate parameters for each process
void findRR(Process proc[], int n, int quantum) {
    findAvgTime(proc, n, quantum);
}

// Function to print process details
void printRR(Process proc[], int n) {
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << "\t"
             << proc[i].arrivalTime << "\t"
             << proc[i].burstTime << "\t"
             << proc[i].completionTime << "\t"
             << proc[i].turnaroundTime << "\t"
             << proc[i].waitingTime << "\n";
    }
}


int main() {
    int n = 5; // Number of processes
    Process proc[5] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 2}, {4, 3, 4}, {5, 4, 1}};
    int quantum = 2; 

    findRR(proc, n, quantum);
    printRR(proc, n);

    return 0;
}
