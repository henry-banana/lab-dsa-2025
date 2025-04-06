#pragma once

#include "../../others/header/helpFunctions.hpp"

#ifndef RADIX_SORT_HPP
#define RADIX_SORT_HPP

template<class T>
T getMax(std::vector<T>& array, size_t& count_comparison);

template<class T>
void countSort(std::vector<T>& array, size_t exp, size_t& count_comparison);

template<class T>
void radixSort(std::vector<T>& array, size_t& count_comparison);

template<class T>
T getMax(std::vector<T>& array);

template<class T>
void countSort(std::vector<T>& array, size_t exp);

template<class T>
void radixSort(std::vector<T>& array);

#endif // RADIX_SORT_HPP