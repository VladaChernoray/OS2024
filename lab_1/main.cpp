#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <functional>
#include <random>
#include <iomanip>


using namespace std;
using namespace std::chrono;

struct ResourceUsage {
    long long comparisons;
    long long assignments;
    long long memory;
    double time_taken;
};

ResourceUsage bubble_sort(int arr[], int size);
ResourceUsage quicksort(int arr[], int size);
ResourceUsage merge_sort(int arr[], int size);
ResourceUsage insert_sort(int arr[], int size);

typedef function<ResourceUsage(int[], int)> SortFunc;

// Generate uniform distribution
void uniform_distribution(int array[], int num) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, INT_MAX);
    for (int i = 0; i < num; ++i) {
        array[i] = distribution(gen);
    }
}

// Generate normal distribution 
void normal_distribut(int array[], int num) {
    std::random_device rd;
    std::mt19937 gen(rd());

    double mean = 0.0; 
    double stddev = 100.0; 

    std::normal_distribution<double> distribution(mean, stddev);

    for (int i = 0; i < num; ++i) {
        array[i] = static_cast<int>(distribution(gen)); 
    }
}
// Generate asymptotic case (better -- sorted data)
void generateSortedData(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }
}
// Generate asymptotic case (worst -- reverse sorted data)
void generateReverseSortedData(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = size - i;
    }
}


// Bubble sort implementation
ResourceUsage bubble_sort(int arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};

    auto start = high_resolution_clock::now();

    for (int i = 0; i < size; ++i) {
        for (int index = 0; index < size - i - 1; ++index) {
            ++usage.comparisons;
            if (arr[index] < arr[index + 1]) {
                int temp;
                temp = arr[index];
                arr[index] = arr[index + 1];
                arr[index + 1] = temp;
                usage.assignments += 3;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    usage.time_taken = duration_cast<duration<double>>(stop - start).count();
    usage.memory = size * sizeof(int);

    return usage;
}

// Quick sort implementation
void swap(int arr[], int idx1, int idx2) {
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

int getPivotPos(int arr[], int start, int end) {
    if (end > start + 1) {
        int middle = start + (end - start) / 2;
        return (arr[start] < arr[middle]) ? ((arr[middle] < arr[end]) ? middle : (arr[end] < arr[start]) ? start : end)
                                          : ((arr[end] < arr[middle]) ? middle : ((arr[start] < arr[end]) ? start : end));
    } else if (end > start)
        return arr[start] < arr[end] ? start : end;
    else if (end == start)
        return start;
}

int partition(int arr[], int start, int pivotPos, int end, ResourceUsage &usage) {
    int pivot = arr[pivotPos];
    swap(arr, pivotPos, end);
    int left = start - 1, right = end;

    while (true) {
        ++usage.comparisons;
        while (arr[++left] < pivot)
            ;
        ++usage.comparisons;
        while (arr[--right] > pivot)
            ;
        if (left < right) {
            swap(arr, left, right);
            ++usage.assignments;
        } else
            break;
    }
    swap(arr, end, left);
    ++usage.assignments;
    return left;
}

void quicksortRecur(int arr[], int start, int end, ResourceUsage &usage) {
    if (start < end) {
        int pivotPos = getPivotPos(arr, start, end);
        pivotPos = partition(arr, start, pivotPos, end, usage);
        quicksortRecur(arr, start, pivotPos - 1, usage);
        quicksortRecur(arr, pivotPos + 1, end, usage);
    }
}

ResourceUsage quicksort(int arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};
    auto start = high_resolution_clock::now();

    quicksortRecur(arr, 0, size - 1, usage);

    auto stop = high_resolution_clock::now();

    usage.time_taken = duration_cast<duration<double>>(stop - start).count();
    usage.memory = size * sizeof(int);

    return usage;
}

// Merge sort implementation
void merge(int arr[], int leftPos, int rightPos, int rightEnd, ResourceUsage &usage) {
    int leftEnd = rightPos - 1, leftPosSaved = leftPos;

    int numElements = rightEnd - leftPos + 1;
    int *temp = new int[numElements]();
    int tempPos = 0;

    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        ++usage.comparisons;
        if (arr[leftPos] < arr[rightPos])
            temp[tempPos++] = arr[leftPos++];
        else
            temp[tempPos++] = arr[rightPos++];
    }

    while (leftPos <= leftEnd) {
        temp[tempPos++] = arr[leftPos++];
        ++usage.assignments;
    }
    while (rightPos <= rightEnd) {
        temp[tempPos++] = arr[rightPos++];
        ++usage.assignments;
    }

    for (int i = 0; i < numElements; i++) {
        arr[leftPosSaved + i] = temp[i];
        ++usage.assignments;
    }

    delete[] temp;
}

void mergeSortRecur(int arr[], int left, int right, ResourceUsage &usage) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSortRecur(arr, left, middle, usage);
        mergeSortRecur(arr, middle + 1, right, usage);
        merge(arr, left, middle + 1, right, usage);
    }
}

ResourceUsage merge_sort(int arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};
    auto start = high_resolution_clock::now();

    mergeSortRecur(arr, 0, size - 1, usage);

    auto stop = high_resolution_clock::now();
    usage.time_taken = duration_cast<duration<double>>(stop - start).count();
    usage.memory = size * sizeof(int);

    return usage;
}

// Insertion sort implementation
void exch(int arr[], int i, int j, ResourceUsage &usage) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    usage.assignments += 3;
}

ResourceUsage insert_sort(int arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};

    auto start = high_resolution_clock::now();

    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0) {
            ++usage.comparisons;
            if (arr[j] > arr[j - 1]) {
                break;
            }
            exch(arr, j, j - 1, usage);
            j--;
        }
    }

    auto stop = high_resolution_clock::now();
    usage.time_taken = duration_cast<duration<double>>(stop - start).count();
    usage.memory = size * sizeof(int);
    return usage;
}


/*
int main() {
    const int size = 1000;
    int numbers[size];

    srand(time(0));
    ResourceUsage bubble_sort_usage;
    ResourceUsage quicksort_usage;
    ResourceUsage merge_sort_usage;
    ResourceUsage insert_sort_usage;

    while (true) {
        cout << "Choose an option:" << endl;
        cout << "1. Bubble Sort" << endl;
        cout << "2. Quick Sort" << endl;
        cout << "3. Merge Sort" << endl;
        cout << "4. Insertion Sort" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;
    
        switch (choice) {
            case 1:
                generateNumbers(numbers, size);
                bubble_sort_usage = bubble_sort(numbers, size);
                cout << "Bubble sort" << endl;
                cout << "Comparisons: " << bubble_sort_usage.comparisons << endl;
                cout << "Assignments: " << bubble_sort_usage.assignments << endl;
                cout << "Time taken: " << bubble_sort_usage.time_taken << " seconds" << endl;
                cout << "Memory used: " << bubble_sort_usage.memory << " bytes" << endl << endl;
                break;
            case 2:
                generateNumbers(numbers, size);
                quicksort_usage = quicksort(numbers, size);
                cout << "Quick sort" << endl;
                cout << "Comparisons: " << quicksort_usage.comparisons << endl;
                cout << "Assignments: " << quicksort_usage.assignments << endl;
                cout << "Time taken: " << quicksort_usage.time_taken << " seconds" << endl;
                cout << "Memory used: " << quicksort_usage.memory << " bytes" << endl << endl;
                break;
            case 3:
                generateNumbers(numbers, size);
                merge_sort_usage = merge_sort(numbers, size);
                cout << "Merge sort" << endl;
                cout << "Comparisons: " << merge_sort_usage.comparisons << endl;
                cout << "Assignments: " << merge_sort_usage.assignments << endl;
                cout << "Time taken: " << merge_sort_usage.time_taken << " seconds" << endl;
                cout << "Memory used: " << merge_sort_usage.memory << " bytes" << endl << endl;
                break;
            case 4:
                generateNumbers(numbers, size);
                insert_sort_usage = insert_sort(numbers, size);
                cout << "Insertion sort" << endl;
                cout << "Comparisons: " << insert_sort_usage.comparisons << endl;
                cout << "Assignments: " << insert_sort_usage.assignments << endl;
                cout << "Time taken: " << insert_sort_usage.time_taken << " seconds" << endl;
                cout << "Memory used: " << insert_sort_usage.memory << " bytes" << endl << endl;
                break;
            case 5:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
*/
int main() {
    const vector<int> sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    
    vector<pair<string, SortFunc>> sortAlgorithms = {
        {"Bubble Sort", bubble_sort},
        {"Quick Sort", quicksort},
        {"Merge Sort", merge_sort},
        {"Insertion Sort", insert_sort}
    };

    cout << "+---------+-------------------+----------------------+-------------------+-------------------+-------------------+-------------------+" << endl;
    cout << "| Array   | Sorting           | Data Generation      |  Comparisons      | Assignments       |  Time taken       | Memory used       |" << endl;
    cout << "| Size    | Algorithm         | Method               |                   |                   |                   |                   |" << endl;
    cout << "+---------+-------------------+----------------------+-------------------+-------------------+-------------------+-------------------+" << endl;

    for (int size : sizes) {
        for (const auto& algorithm : sortAlgorithms) {
            for (int dataGen = 0; dataGen < 4; ++dataGen) {
                vector<int> numbers(size);
                switch (dataGen) {
                    case 0: uniform_distribution(numbers.data(), size); break;
                    case 1: normal_distribut(numbers.data(), size); break;
                    case 2: generateSortedData(numbers.data(), size); break;
                    case 3: generateReverseSortedData(numbers.data(), size); break;
                }

                SortFunc sortingAlgorithm = algorithm.second;
                ResourceUsage usage = sortingAlgorithm(numbers.data(), size);

                cout << "| " << setw(8) << left << size;
                cout << "| " << setw(18) << left << algorithm.first;
                cout << "| ";
                switch (dataGen) {
                    case 0: cout << setw(21) << left << "Uniform Distribution"; break;
                    case 1: cout << setw(21) << left << "Normal Distribution"; break;
                    case 2: cout << setw(21) << left << "Sorted Data"; break;
                    case 3: cout << setw(21) << left << "Reverse Sorted Data"; break;
                }
                cout << "| " << setw(18) << left << usage.comparisons;
                cout << "| " << setw(18) << left << usage.assignments;
                cout << "| " << setw(18) << left << fixed << setprecision(6) << usage.time_taken;
                cout << "| " << setw(18) << left << usage.memory << "|" << endl;
            }
            cout << "+---------+-------------------+----------------------+-------------------+-------------------+-------------------+-------------------+" << endl;
        }
    }

    return 0;
}