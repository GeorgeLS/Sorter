#include <iostream>
#include "Sort.h"

void printArray(int *array, size_t length) {
    for (size_t i = 0U; i != length; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl << std::endl;
}

void resetArray(int *array, size_t length) {
    for (size_t i = 0U; i != length; ++i) {
        array[i] = static_cast<int>(length - i);
    }
}

template <Sort::Algorithm Algorithm> using IntSorter = Sort::Sorter<int, Algorithm>;

int main() {
    IntSorter<Sort::BubbleSort> bubbleSorter{};
    IntSorter<Sort::InsertionSort> insertionSorter{};
    IntSorter<Sort::MergeSort> mergeSorter{};
    IntSorter<Sort::QuickSort> quickSorter{};
    IntSorter<Sort::SelectionSort> selectionSorter{};
    IntSorter<Sort::ShellSort> shellSorter{};

    size_t length = 10000U;
    int *array = (int*) malloc(length * sizeof(int));

    resetArray(array, length);
    std::cout << "Original Array" << std::endl;
    printArray(array, length);

    std::cout << "Bubble Sort" << std::endl;
    bubbleSorter(array, length);
    printArray(array, length);

    resetArray(array, length);
    std::cout << "Insertion Sort" << std::endl;
    insertionSorter(array, length);
    printArray(array, length);

    resetArray(array, length);
    std::cout << "Merge Sort" << std::endl;
    mergeSorter(array, 0, length);
    printArray(array, length);

    resetArray(array, length);
    std::cout << "Quick Sort" << std::endl;
    quickSorter(array, 0, length);
    printArray(array, length);

    resetArray(array, length);
    std::cout << "Selection Sort" << std::endl;
    selectionSorter(array, length);
    printArray(array, length);

    resetArray(array, length);
    std::cout << "Shell Sort" << std::endl;
    shellSorter(array, length);
    printArray(array, length);

    return EXIT_SUCCESS;
}