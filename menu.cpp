#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {i++;
	std::swap(arr[i], arr[j]);
					}
}
std::swap(arr[i + 1], arr[high]);
return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
if (low < high) {
int pi = partition(arr, low, high);


    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

}

void printMenu() {
std::cout << "==== Sorting Algorithms ====" << std::endl;
std::cout << "1. Selection Sort" << std::endl;
std::cout << "2. Bubble Sort" << std::endl;
std::cout << "3. Insertion Sort" << std::endl;
std::cout << "4. Merge Sort" << std::endl;
std::cout << "5. Quick Sort" << std::endl;
std::cout << "============================" << std::endl;
std::cout << "Enter your choice (1-5): ";
}

void sortNumbers(std::vector<int>& numbers, int choice) {
switch (choice) {
case 1:
selectionSort(numbers);
break;
case 2:
bubbleSort(numbers);
break;
case 3:
insertionSort(numbers);
break;
case 4:
mergeSort(numbers, 0, numbers.size() - 1);
break;
case 5:
quickSort(numbers, 0, numbers.size() - 1);
break;
default:
std::cout << "Invalid choice!" << std::endl;
return;
}
std::cout << "Instancia numerica ordenada com sucesso!"<< std::endl;
std::cout << "verifique o arquivo sorted.txt"<< std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "==== Instâncias numéricas ====" << std::endl;
        std::cout << "    Arquivos disponíveis: " << std::endl;
        std::cout << "        num.1000.1.in" << std::endl;
        std::cout << "        num.1000.2.in" << std::endl;
        std::cout << "        num.1000.3.in" << std::endl;
        std::cout << "        num.10000.1.in" << std::endl;
        std::cout << "        num.10000.2.in" << std::endl;
        std::cout << "        num.10000.3.in" << std::endl;
        std::cout << "        num.100000.1.in" << std::endl;
        std::cout << "        num.100000.2.in" << std::endl;
        std::cout << "        num.100000.3.in" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Para usar este programa, selecione o"<< std::endl;
        std::cout << " nome do arquivo que deseja ordenar." << std::endl;
        std::cout << "Exemplo: " << argv[0] << " num.1000.1.in" << std::endl;
        return 1;
    }

// Open the output file for writing
std::ofstream outputFile("sorted.txt");
if (!outputFile) {
    std::cerr << "Failed to open output file: output.txt" << std::endl;
    return 1;
}

for (int i = 1; i < argc; i++) {
    std::ifstream inputFile(argv[i]);
    if (!inputFile) {
        std::cerr << "Failed to open file: " << argv[i] << std::endl;
        continue;
    }

    std::vector<int> numbers;
    std::string line;
    while (std::getline(inputFile, line)) {
        int num = std::stoi(line);
        numbers.push_back(num);
    }

    inputFile.close();

    printMenu();
    int choice;
    std::cin >> choice;

    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    sortNumbers(numbers, choice);

    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();

    outputFile << "Sorted numbers for file: " << argv[i] << ":" << std::endl;
    for (int j = 0; j < numbers.size(); j++) {
        outputFile << numbers[j] << std::endl;
    }
    outputFile << "Elapsed time: " << elapsedTime << " seconds." << std::endl;
}

outputFile.close();

return 0;

}
