#include <iostream>
#include <vector>

using namespace std;

void firstFit(const vector<int>& blockSize, const vector<int>& processSize) {
    int m = blockSize.size();
    int n = processSize.size();
    vector<int> allocation(n, -1); // Initialize to -1 (no allocation)

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;       // Allocate block j to process i
                blockSize[j] -= processSize[i]; // Update available space
                break; // Move to the next process
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1 << endl;
        } else {
            cout << "Not Allocated\n";
        }
    }
}

int main() {
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};

    firstFit(blockSize, processSize);
    
    return 0;
}
