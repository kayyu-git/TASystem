#include "MAsDevCalculator.h"
#include "Helpers.h"
#include "ThreadSafeCout.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

void MAsDevCalculator::addDataItem(const double data)
{
    while (myRawData.size() >= myLookBack) myRawData.pop_front();

    myRawData.push_back(data);

    if (myRawData.size() == myLookBack)
    {
        myTaskQ->push(std::bind(&MAsDevCalculator::calculate, this, myRawData));
    }
}

void MAsDevCalculator::changeSettings(const std::string& setting)
{
	myTaskQ->push(std::bind(&MAsDevCalculator::doChangeSettings, this, setting));
}
bool MAsDevCalculator::calculate(std::deque<double>& data)
{
    if (!isnan(myLastMA) && !isnan(myLastSDev))
    {
        double delta = std::fabs(data.back() - myLastMA);
        if (delta > myLastSDev)
        {
            double nSDev = delta / myLastSDev;
            bool isBelowMA = (data.back() < myLastMA);
            // notify listeners
            for each (auto l in myListeners)
            {
                l->addDataItem(TADataItem(myTicker, data.back(), isBelowMA, nSDev, myLastMA));
            }
        }
    }

	myLastMA = average(data);
	myLastSDev = stdv(data);

	std::stringstream stream;
    stream << outputData(data);
	stream << "MA: " << myLastMA << "\n" << "sDev: " << myLastSDev << "\n";
	myCoutput.addDataItem(stream.str());
	//myTscout("MA: ", average(data), "\n", "sDev: ", stdv(data), "\n");
    //tscout("sDev: ", stdv(data), "\n");
	//this->sync();

    return false;
}

bool MAsDevCalculator::doChangeSettings(const std::string& setting)
{
	mySettings = setting;

	return false;
}
