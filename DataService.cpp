#include "DataService.h"

#include <fstream>
#include <string>

void DataService::retrieveData()
{
	std::fstream marketData(myFileName);

	while (!marketData.eof())
	{
		std::string line;
		std::getline(marketData, line);
		double data = stod(line);
		for each (DataListenerPtr l in myListeners)
		{
			l->addDataItem(data);
		}
	}
}