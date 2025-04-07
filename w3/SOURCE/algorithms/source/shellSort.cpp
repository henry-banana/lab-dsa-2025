#include "../header/shellSort.h"

template <class T>
void shellSort(std::vector<T> &arr, size_t &count_comparison) {
    count_comparison = 0; // Initialize comparison counter
    size_t n = arr.size();
    
    // Start with a large gap and reduce it
    for (size_t gap = n / 2; ++count_comparison && gap > 0; gap /= 2) {
        // Perform a gapped insertion sort
        for (size_t i = gap; ++count_comparison && i < n; ++i) {
            T temp = arr[i];
            size_t j = i;

            // Shift earlier gap-sorted elements up until the correct location is found
            while (++count_comparison && j >= gap && ++count_comparison && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

template <class T>
void shellSort(std::vector<T> &arr) {
    size_t n = arr.size();

    // Start with a large gap and reduce it
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort
        for (size_t i = gap; i < n; ++i) {
            T temp = arr[i];
            size_t j = i;

            // Shift earlier gap-sorted elements up until the correct location is found
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// INSTANTIATION
//shellSort with Compare
template void shellSort(std::vector<int>&,  size_t&);
template void shellSort(std::vector<long long>&, size_t&);
template void shellSort(std::vector<float>&, size_t&);
template void shellSort(std::vector<double>&, size_t&);
template void shellSort(std::vector<char>&, size_t&);

// shellSort
template void shellSort(std::vector<int>&);
template void shellSort(std::vector<long long>&);
template void shellSort(std::vector<float>&);
template void shellSort(std::vector<double>&);
template void shellSort(std::vector<char>&);

