#pragma once

class DataListener
{
public:
	virtual void addDataItem(const double data) = 0;
};

typedef DataListener* DataListenerPtr;
