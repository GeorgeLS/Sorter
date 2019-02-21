#ifndef SORT_LIBRARY_H
#define SORT_LIBRARY_H

#include <cstddef>
#include <random>

namespace Sort {
    enum Algorithm {
        BubbleSort,
        InsertionSort,
        SelectionSort,
        ShellSort,
        QuickSort,
        MergeSort
    };

    template<typename T, Sort::Algorithm Algorithm, bool Descending = false>
    class Sorter {
    private:
        std::default_random_engine generator;

        void swap(T &v1, T &v2) {
            T tmp = v1;
            v1 = v2;
            v2 = tmp;
        }

        void bubbleSort(T *data, size_t length) {
            bool swapped;
            do {
                swapped = false;
                for (size_t i = 0; i != length - 1; ++i) {
                    if ((Descending) ? data[i] < data[i + 1] : data[i] > data[i + 1]) {
                        swap(data[i], data[i + 1]);
                        swapped = true;
                    }
                }
                --length;
            } while (swapped);
        }

        void insertionSort(T *data, size_t length) {
            for (ssize_t i = 0; i != length; ++i) {
                T tmp = data[i];
                ssize_t j = i - 1;
                while (j >= 0) {
                    if ((Descending) ? data[j] < tmp : data[j] > tmp) {
                        data[j + 1] = data[j];
                    } else break;
                    --j;
                }
                data[j + 1] = tmp;
            }
        }

        void selectionSort(T *data, size_t length) {
            for (size_t i = 0; i != length - 1; ++i) {
                size_t index = i;
                for (size_t j = i + 1; j != length; ++j) {
                    if ((Descending) ? data[j] > data[index] : data[j] < data[index]) {
                        index = j;
                    }
                }
                swap(data[i], data[index]);
            }
        }

        void shellSort(T *data, size_t length) {
            ssize_t interval = 1;
            while (interval < length / 3) {
                interval = interval * 3 + 1;
            }
            while (interval > 0) {
                for (ssize_t i = interval; i != length; ++i) {
                    T toInsert = data[i];
                    ssize_t j = i;
                    while ((j > interval - 1)) {
                        if ((Descending) ? data[j - interval] <= toInsert : data[j - interval] >= toInsert) {
                            data[j] = data[j - interval];
                            j -= interval;
                        } else break;
                    }
                    data[j] = toInsert;
                }
                interval = (interval - 1) / 3;
            }
        }

        void merge(T *data, ssize_t left_index, ssize_t middle_index, ssize_t right_index) {
            ssize_t left_length = middle_index - left_index + 1;
            ssize_t right_length = right_index - middle_index;
            T *left_aux = (T*) malloc(left_length * sizeof(int));
            T *right_aux = (T*) malloc(right_length * sizeof(int));
            for (ssize_t i = 0; i != left_length; ++i) {
                left_aux[i] = data[left_index + i];
            }
            for (ssize_t i = 0; i != right_length; ++i) {
                right_aux[i] = data[middle_index + i + 1];
            }
            ssize_t i = 0;
            ssize_t j = 0;
            ssize_t k = left_index;
            while (i < left_length && j < right_length) {
                if ((Descending) ? left_aux[i] >= right_aux[j] : left_aux[i] <= right_aux[j]) {
                    data[k] = left_aux[i++];
                } else {
                    data[k] = right_aux[j++];
                }
                ++k;
            }
            while (i < left_length) {
                data[k++] = left_aux[i++];
            }
            while (j < right_length) {
                data[k++] = right_aux[j++];
            }
            free(left_aux);
            free(right_aux);
        }

        void mergeSort(T *data, size_t left_index, size_t right_index) {
            if (left_index < right_index) {
                size_t middle_index = left_index + ((right_index - left_index) >> 1);
                mergeSort(data, left_index, middle_index);
                mergeSort(data, middle_index + 1, right_index);
                merge(data, left_index, middle_index, right_index);
            }
        }

        ssize_t partition(T *data, ssize_t left_index, ssize_t right_index) {
            std::uniform_int_distribution<ssize_t> distribution(static_cast<ssize_t >(left_index),
                                                                static_cast<ssize_t >(right_index));
            ssize_t random_index = distribution(generator);
            swap(data[random_index], data[right_index]);
            T pivot = data[right_index];
            ssize_t i = left_index - 1;
            for (ssize_t j = left_index; j != right_index; ++j) {
                if ((Descending) ? data[j] >= pivot : data[j] <= pivot) {
                    ++i;
                    swap(data[i], data[j]);
                }
            }
            swap(data[i + 1], data[right_index]);
            return static_cast<ssize_t>(i + 1);
        }

        void quickSort(T *data, ssize_t left_index, ssize_t right_index) {
            while (left_index < right_index) {
                ssize_t partition_index = partition(data, left_index, right_index);
                if (partition_index - left_index < right_index - partition_index) {
                    quickSort(data, left_index, partition_index - 1);
                    left_index = partition_index + 1;
                } else {
                    quickSort(data, partition_index + 1, right_index);
                    right_index = partition_index - 1;
                }
            }
        }

        void sort(T *data, size_t length) {
            switch (Algorithm) {
                case BubbleSort:
                    bubbleSort(data, length);
                    break;
                case InsertionSort:
                    insertionSort(data, length);
                    break;
                case SelectionSort:
                    selectionSort(data, length);
                    break;
                case ShellSort:
                    shellSort(data, length);
                    break;
            }
        }

        void sort(T *data, size_t left_index, size_t right_index) {
            switch (Algorithm) {
                case MergeSort:
                    mergeSort(data, left_index, right_index - 1);
                    break;
                case QuickSort:
                    quickSort(data, left_index, right_index - 1);
                    break;
            }
        }

    public:
        Sorter() = default;

        ~Sorter() = default;

        void operator()(T *data, size_t length) {
            sort(data, length);
        };

        void operator()(T *data, size_t left_index, size_t right_index) {
            sort(data, left_index, right_index);
        }
    };
}

#endif