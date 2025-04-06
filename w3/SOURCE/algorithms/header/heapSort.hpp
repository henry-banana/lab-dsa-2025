#pragma once

#include "../../others/header/helpFunctions.hpp"

#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

template<class T>
void heapify(std::vector<T>& array, size_t n, size_t i, size_t& count_comparison);

template<class T>
void heapSort(std::vector<T>& array, size_t& count_comparison);

template<class T>
void heapify(std::vector<T>& array, size_t n, size_t i);

template<class T>
void heapSort(std::vector<T>& array);

#endif // HEAP_SORT_HPP