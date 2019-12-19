#include "COutput.h"

#include <iostream>


void COutput::addDataItem(const std::string& text)
{
    myTaskQ->push(std::bind(&COutput::display, this, text));
}

bool COutput::display(const std::string& text)
{
	std::cout << text.c_str() << std::endl;

    return false;
}
