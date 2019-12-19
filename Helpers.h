#pragma once

#include <deque>
#include <string>

double stdv(const std::deque<double>& numbers);

double average(const std::deque<double>& numbers);

std::string outputData(const std::deque<double>& numbers);

double expAverage(const std::deque<double>& numbers, double prevEMA);