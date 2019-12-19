#pragma once

#include "DataListener.h"

#include <vector>
#include <string>

class DataService
{
public:
	DataService(const std::string& fileName) : myFileName(fileName)
	{
	}

	~DataService()
	{
	}

	void registerListener(DataListenerPtr l)
	{
		myListeners.push_back(l);
	}

	void retrieveData();

private:
	const std::string& myFileName;

	std::vector<DataListenerPtr> myListeners;
};