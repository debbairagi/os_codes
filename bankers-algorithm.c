#include <iostream>
using namespace std;

void calculateNeed(int need[][10], int max[][10], int allocation[][10], int P, int R) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int processes[], int available[], int max[][10], int allocation[][10], int P, int R) {
    int need[10][10];
    calculateNeed(need, max, allocation, P, R);

    bool finish[10] = {0};
    int safeSequence[10];
    int work[10];
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state." << endl;
            return false;
        }
    }
    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < P; i++) {
        cout << safeSequence[i] << " ";
    }
    cout << endl;
    return true;
}

int main() {
    int P, R;

    cout << "Enter the number of processes: ";
    cin >> P;
    cout << "Enter the number of resource types: ";
    cin >> R;

    int processes[P];
    for (int i = 0; i < P; i++) {
        processes[i] = i;
    }

    int allocation[10][10];
    int max[10][10];
    int available[10];

    cout << "Enter the Allocation Matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < R; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the Max Matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < R; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the Available Resources:\n";
    for (int j = 0; j < R; j++) {
        cin >> available[j];
    }

    isSafe(processes, available, max, allocation, P, R);

    return 0;
}
