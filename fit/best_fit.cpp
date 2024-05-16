#include <iostream>
#include <vector>
using namespace std;

void implementBestFit(const vector<int>& blockSize, const vector<int>& processSize) {
    int numBlocks = blockSize.size();
    int numProcesses = processSize.size();

    vector<int> allocation(numProcesses, -1);
    vector<bool> occupied(numBlocks, false);

    // Create a copy of blockSize to avoid modifying the original
    vector<int> remainingBlockSize(blockSize); 

    for (int i = 0; i < numProcesses; i++) {
        int bestFitIndex = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (!occupied[j] && remainingBlockSize[j] >= processSize[i]) {
                if (bestFitIndex == -1 || remainingBlockSize[j] < remainingBlockSize[bestFitIndex]) {
                    bestFitIndex = j;
                }
            }
        }

        if (bestFitIndex != -1) {
            allocation[i] = bestFitIndex;
            occupied[bestFitIndex] = true;
            remainingBlockSize[bestFitIndex] -= processSize[i]; 
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << i + 1 << "\t\t\t" << processSize[i] << "\t\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1 << endl; // Display original block numbers
        } else {
            cout << "Not Allocated\n";
        }
    }
}

int main() {
    vector<int> blockSize = {5, 4, 3, 6, 7};
    vector<int> processSize = {1, 3, 5, 3};

    implementBestFit(blockSize, processSize); // Pass blockSize by const reference

    return 0;
}
