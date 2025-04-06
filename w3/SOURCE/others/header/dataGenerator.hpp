#pragma once

#include "helpFunctions.hpp"

#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

template <class T>
void generateRandomData(std::vector<int> &arr, int n);
void generateSortedData(std::vector<int> &arr, int n);
void generateReverseData(std::vector<int> &arr, int n);
void generateNearlySortedData(std::vector<int> &arr, int n);
void generateData(std::vector<int> &arr, int n, int dataType);
std::string getDataOrderName(int data_order_id);
int getDataOrderID(char agr_flag[]);

#endif // DATA_GENERATOR_HPP