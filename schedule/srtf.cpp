#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;       
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int remainingTime; 
};

void findWaitingTime(Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;
    while (completed != n) {
        int shortest = -1;
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 &&
                (shortest == -1 || proc[i].remainingTime < proc[shortest].remainingTime)) {
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            currentTime++;
            continue; 
        }

        proc[shortest].remainingTime--;
        currentTime++;

        if (proc[shortest].remainingTime == 0) {
            completed++;
            proc[shortest].completionTime = currentTime;
            proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        }
    }
}

void findTurnaroundTime(Process proc[], int n) { /* Not needed, calculated in findWaitingTime */ }

void findCompletionTime(Process proc[], int n) { /* Not needed, calculated in findWaitingTime */ }

void findSRTF(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime; 
    }
    findWaitingTime(proc, n);
}

void printSRTF(Process proc[], int n) {
    cout << "SRTF Scheduling:" << endl;
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;

    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << "\t" << proc[i].arrivalTime << "\t\t"
             << proc[i].burstTime << "\t\t" << proc[i].completionTime << "\t\t"
             << proc[i].turnaroundTime << "\t\t" << proc[i].waitingTime << endl;
    }
}

int main() {
    int n = 5; 
    Process proc[5] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 2}, {4, 3, 4}, {5, 4, 1}};
    findSRTF(proc, n);
    printSRTF(proc, n);

    return 0;
}
