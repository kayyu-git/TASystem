#include "Helpers.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

double stdv(const deque<double>& numbers) 
{
	double variance = 0;
	int x, size = numbers.size();

	double mean = average(numbers);

	for (x = 0; x < size; ++x) 
    {
		variance += pow(numbers[x] - mean, 2);
	}
	variance = variance / size;

	return sqrt(variance);
}

double average(const deque<double>& numbers) 
{
	double sum = 0;
	int x, size = numbers.size();
	for (x = 0; x < size; ++x) 
    {
		sum += numbers[x];
	}

	return sum / size;
}

double expAverage(const deque<double>& numbers, double prevEMA) {
	double multiplier = (2.0 / (numbers.size() + 1.0));
	return (average(numbers) * multiplier) + (prevEMA * (1 - multiplier));
}

std::string outputData(const deque<double>& numbers) 
{
	std::stringstream stream;
	stream << "\n";
	for (size_t x = 0; x < numbers.size(); ++x) 
    {
		stream << numbers[x] << ", ";
	}
	stream << "\n";
	return stream.str();
}
