#pragma once

#include "sortExperiment.hpp"

#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

void executeWithCommandLine(SortExperiment &experiment, int argc, char **argv);
bool parseCommandLine(SortExperiment &experiment, int argc, char **argv);
void handleAlgorithmMode(SortExperiment &experiment, char **argv);
void handleInputOutput(SortExperiment &experiment, char **argv);

#endif