#include "Analyzer.h"

#include <sstream>

void Analyzer::addDataItem(const TADataItem& data)
{
    myTaskQ->push(std::bind(&Analyzer::calculate, this, data));
}

bool Analyzer::calculate(const TADataItem& data)
{
    std::stringstream stream;
    stream << "px for " << data.ticker << ", " << data.price << ", is " << data.nSDev 
            << " std dev " << (data.isBelowMA ? "below" : "above") << " moving average, "
            << data.ma << std::endl;
    myCoutput.addDataItem(stream.str());

    return false;
}
