#include "EMACalculator.h"
#include "Helpers.h"
#include "ThreadSafeCout.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

void EMACalculator::addDataItem(const double data) {
	while (myRawData.size() >= myLookBack) myRawData.pop_front();

	myRawData.push_back(data);

	if (myRawData.size() == myLookBack)
	{
		myTaskQ->push(std::bind(&EMACalculator::calculate, this, myRawData));
	}
}

bool EMACalculator::calculate(std::deque<double>& data)
{
	std::stringstream stream;
	stream << outputData(data);
	if (counter == 0) {
		stream << "EMA: " << average(data) << "\n";
		//std::cout << stream.str();
		myCoutput.addDataItem(stream.str());
		prevEMA = average(data);
		//this->sync();
		++counter;
	}
	else {
		double temp = expAverage(data, prevEMA);
		prevEMA = temp;
		stream << "EMA: " << prevEMA << "\n";
		myCoutput.addDataItem(stream.str());
		//tscout2("EMA: ", prevEMA, "\n");
		//this->sync();
	}

	return false;
}