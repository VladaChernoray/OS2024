#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <functional>
#include <random>
#include <iomanip>
#include <filesystem>

using namespace std;
using namespace std::chrono;

namespace fs = std::filesystem;

struct ResourceUsage {
    long long comparisons;
    long long assignments;
    long long memory;
    double time_taken;
};

ResourceUsage bubble_sort(double arr[], int size);
ResourceUsage quicksort(double arr[], int size);
ResourceUsage merge_sort(double arr[], int size);
ResourceUsage insert_sort(double arr[], int size);

typedef function<ResourceUsage(double[], int)> SortFunc;

// Generate uniform distribution
void uniform_distribution(double array[], int num) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < num; ++i) {
        array[i] = distribution(gen);
    }
}

// Generate normal distribution 
void normal_distribut(double array[], int num) {
    std::random_device rd;
    std::mt19937 gen(rd());

    double mean = 0.0; 
    double stddev = 100.0; 

    std::normal_distribution<double> distribution(mean, stddev);

    for (int i = 0; i < num; ++i) {
        array[i] = distribution(gen); 
    }
}

// Generate asymptotic case (better -- sorted data)
void generateSortedData(double array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }
}

// Generate asymptotic case (worst -- reverse sorted data)
void generateReverseSortedData(double array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = size - i;
    }
}

ResourceUsage bubble_sort(double arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};

    auto start = high_resolution_clock::now();

    // Memory used by the array itself
    usage.memory += size * sizeof(double);

    // Memory used by other variables
    usage.memory += sizeof(int); // for 'i'
    usage.memory += sizeof(int); // for 'index'
    usage.memory += sizeof(double); // for 'temp'

    for (int i = 0; i < size; ++i) {
        for (int index = 0; index < size - i - 1; ++index) {
            ++usage.comparisons;
            if (arr[index] < arr[index + 1]) {
                double temp;
                temp = arr[index];
                arr[index] = arr[index + 1];
                arr[index + 1] = temp;
                usage.assignments += 3;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    usage.time_taken = duration_cast<duration<double>>(stop - start).count();

    return usage;
}

// Quick sort implementation
void swap(double arr[], int idx1, int idx2) {
    double tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

int getPivotPos(double arr[], int start, int end) {
    if (end > start + 1) {
        int middle = start + (end - start) / 2;
        return (arr[start] < arr[middle]) ? ((arr[middle] < arr[end]) ? middle : (arr[end] < arr[start]) ? start : end)
                                          : ((arr[end] < arr[middle]) ? middle : ((arr[start] < arr[end]) ? start : end));
    } else if (end > start)
        return arr[start] < arr[end] ? start : end;
    else if (end == start)
        return start;
}

int partition(double arr[], int start, int pivotPos, int end, ResourceUsage &usage) {
    double pivot = arr[pivotPos];
    swap(arr, pivotPos, end);
    int left = start - 1, right = end;

    while (true) {
        ++usage.comparisons;
        while (arr[++left] < pivot);
        while (right > 0 && arr[--right] > pivot)
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

void quicksortRecur(double arr[], int start, int end, ResourceUsage &usage) {
    if (start < end) {
        int pivotPos = getPivotPos(arr, start, end);
        pivotPos = partition(arr, start, pivotPos, end, usage);
        quicksortRecur(arr, start, pivotPos - 1, usage);
        quicksortRecur(arr, pivotPos + 1, end, usage);
    }
}

ResourceUsage quicksort(double arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};
    auto start = high_resolution_clock::now();

    quicksortRecur(arr, 0, size - 1, usage);

    auto stop = high_resolution_clock::now();

    usage.time_taken = duration_cast<duration<double>>(stop - start).count();
    
    usage.memory += size * sizeof(double);

    int recursionDepth = log2(size) * 2; 
    int stackFrameSize = sizeof(double) * 3; 
    usage.memory += recursionDepth * stackFrameSize;
    return usage;
}

// Merge sort implementation
void merge(double arr[], int leftPos, int rightPos, int rightEnd, ResourceUsage &usage) {
    int leftEnd = rightPos - 1, leftPosSaved = leftPos;

    int numElements = rightEnd - leftPos + 1;
    double *temp = new double[numElements](); // Dynamically allocated temporary array
    usage.memory += numElements * sizeof(double); // Memory used by temp array
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

void mergeSortRecur(double arr[], int left, int right, ResourceUsage &usage) {
    if (left < right) {
        int middle = left + (right - left) /        2;
        mergeSortRecur(arr, left, middle, usage);
        mergeSortRecur(arr, middle + 1, right, usage);
        merge(arr, left, middle + 1, right, usage);
    }
}

ResourceUsage merge_sort(double arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};
    auto start = high_resolution_clock::now();

    mergeSortRecur(arr, 0, size - 1, usage);

    auto stop = high_resolution_clock::now();
    usage.time_taken = duration_cast<duration<double>>(stop - start).count();

    // Memory used by the array itself
    usage.memory += size * sizeof(double);

    // Memory used by other variables (already counted in merge function)

    return usage;
}
// Insertion sort implementation
void exch(double arr[], int i, int j, ResourceUsage &usage) {
    double tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    usage.assignments += 3;
}

ResourceUsage insert_sort(double arr[], int size) {
    ResourceUsage usage = {0, 0, 0, 0};

    auto start = high_resolution_clock::now();

    // Memory used by the array itself
    usage.memory += size * sizeof(double);

    // Memory used by other variables
    usage.memory += sizeof(int); // for 'i'
    usage.memory += sizeof(int); // for 'j'
    usage.memory += sizeof(double); // for 'tmp'
    usage.memory += sizeof(ResourceUsage); // for 'usage'

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

    return usage;
}


int main() {
    const vector<int> sizes = {10000, 20000, 30000, 40000, 50000};
    const vector<int> sizes_for = {2000};
    int counter = 100;

    vector<pair<string, SortFunc>> sortAlgorithms = {
        {"Bubble Sort", bubble_sort},
        {"Quick Sort", quicksort},
        {"Merge Sort", merge_sort},
        {"Insertion Sort", insert_sort}
    };

    vector<pair<string, function<void(double[], int)>>> dataGenerators = {
        {"Uniform Distribution", uniform_distribution},
        {"Normal Distribution", normal_distribut},
        {"Sorted Data", generateSortedData},
        {"Reverse Sorted Data", generateReverseSortedData}
    };

    cout << "Sorting average results written to sorting_average_results_for_double.txt" << endl;

    ofstream outputFile("tables/sorting_average_results_for_double.txt");


    if (!outputFile.is_open()) {
        cout << "Failed to open output file." << endl;
        return 1;
    }

    for (const auto& dataGen : dataGenerators) {
        outputFile << "Data Generator: " << dataGen.first << endl;

        for (const auto& algorithm : sortAlgorithms) {
            outputFile << "Sorting Algorithm: " << algorithm.first << endl;

            long long totalComparisons = 0;
            long long totalAssignments = 0;
            long long totalMemory = 0;

            for (int size_for : sizes_for) {
                double totalTime = 0.0;

                for (int i = 0; i < counter; ++i) {
                    double* arr = new double[size_for];                    
                    dataGen.second(arr, size_for);

                    ResourceUsage result = algorithm.second(arr, size_for);
                    totalTime += result.time_taken;
                    totalComparisons += result.comparisons;
                    totalAssignments += result.assignments;
                    totalMemory += result.memory;

                    delete[] arr;
                }

                double averageTime = totalTime / (counter * 1.0);
                long long averageComparisons = totalComparisons / counter;
                long long averageAssignments = totalAssignments / counter;
                long long averageMemory = totalMemory / counter;

                outputFile << "Size: " << size_for << endl
                           << "Average Time: " << averageTime << endl
                           << "Average Comparisons: " << averageComparisons << endl
                           << "Average Assignments: " << averageAssignments << endl
                           << "Average Memory Used: " << averageMemory << " bytes" << endl;
            }

            outputFile << endl;
        }
        outputFile << "-----------------------------------------------" << endl;
    }

    outputFile.close();

    cout << "Sorting results written to sorting_results_for_double.txt" << endl;

    ofstream outputFile_2("tables/sorting_results_for_double.txt", ios::out);

    outputFile_2 << "+---------+-------------------+----------------------+-------------------+-------------------+-------------------+-------------------+" << endl;
    outputFile_2 << "| Array   | Sorting           | Data Generation      |  Comparisons      | Assignments       |  Time taken       | Memory used       |" << endl;
    outputFile_2 << "| Size    | Algorithm         | Method               |                   |                   |                   |                   |" << endl;
    outputFile_2 << "+---------+-------------------+----------------------+-------------------+-------------------+-------------------+-------------------+" << endl;

   for (int size : sizes) {
        for (const auto& algorithm : sortAlgorithms) {
            for (const auto& dataGen : dataGenerators) { 
                vector<double> numbers(size);
                dataGen.second(numbers.data(), size); 

                SortFunc sortingAlgorithm = algorithm.second;
                ResourceUsage usage = sortingAlgorithm(numbers.data(), size);

                outputFile_2 << "| " << setw(8) << left << size;
                outputFile_2 << "| " << setw(18) << left << algorithm.first;
                outputFile_2 << "| " << setw(21) << left << dataGen.first;
                outputFile_2 << "| " << setw(18) << left << usage.comparisons;
                outputFile_2 << "| " << setw(18) << left << usage.assignments;
                outputFile_2 << "| " << setw(18) << left << fixed << setprecision(6) << usage.time_taken;
                outputFile_2 << "| " << setw(18) << left << usage.memory << "|" << endl;
            }
            outputFile_2 << "+---------+-------------------+----------------------+-------------------+-------------------+-------------------+-------------------+" << endl;
        }
    }
    outputFile_2.close();


    string newDirectory = "data/double";
    fs::create_directory(newDirectory);

    for (const auto& dataGen : dataGenerators) {
        string folderName = newDirectory + "/Data_" + dataGen.first;
        fs::create_directory(folderName);
        
        for (int size : sizes) {
            for (const auto& algorithm : sortAlgorithms) {
                vector<double> numbers(size);
                dataGen.second(numbers.data(), size); 

                SortFunc sortingAlgorithm = algorithm.second;
                ResourceUsage usage = sortingAlgorithm(numbers.data(), size);

                string fileName = folderName + "/" + algorithm.first + ".txt";
                ofstream outputFile_2(fileName, ios::app);
                outputFile_2 << size << " " << usage.time_taken << endl;
                outputFile_2.close();
            }
        }
    }
    return 0;
}


