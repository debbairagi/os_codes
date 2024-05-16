#include <iostream>

using namespace std;

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;  // Waiting time for the first process is 0

    // Calculating waiting time for each process
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time for each process
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAverageTimes(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt);

    // Function to find turn around time for all processes
    findTurnaroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    cout << "Processes  Burst time  Waiting time  Turnaround time\n";

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << "   " << processes[i] << "\t\t" << bt[i] << "\t    " << wt[i] << "\t\t    " << tat[i] << endl;
    }

    cout << "\nAverage waiting time = " << (float)total_wt / n << endl;
    cout << "Average turnaround time = " << (float)total_tat / n << endl;
}

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int processes[n], burst_time[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        cout << "Enter burst time for process " << processes[i] << ": ";
        cin >> burst_time[i];
    }

    findAverageTimes(processes, n, burst_time);

    return 0;
}
