#pragma once

#include "../../others/header/helpFunctions.hpp"

#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

template<class T>
void Merge(std::vector<T>& array, size_t left, size_t mid, size_t right, size_t& count_comparison);

template<class T>
void impleMergeSort(std::vector<T>& array, size_t left, size_t right, size_t& count_comparison);

template<class T>
void mergeSort(std::vector<T>& array, size_t& count_comparison);

template<class T>
void Merge(std::vector<T>& array, size_t left, size_t mid, size_t right);

template<class T>
void impleMergeSort(std::vector<T>& array, size_t left, size_t right);

template<class T>
void mergeSort(std::vector<T>& array);
#endif // MERGE_SORT_HPP