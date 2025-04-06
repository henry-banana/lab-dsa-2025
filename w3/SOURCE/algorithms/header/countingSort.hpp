#pragma once

#include "../../others/header/helpFunctions.hpp"

#ifndef COUNTING_SORT_HPP
#define COUNTING_SORT_HPP

template<class T>
void countingSort(std::vector<T>& array, size_t& count_comparison);

template<class T>
void countingSort(std::vector<T>& array);

#endif // COUNTING_SORT_HPP