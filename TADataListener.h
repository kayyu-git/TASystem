#pragma once

struct TADataItem
{
    TADataItem(const std::string& t, double px, bool belowMA, double ns, double a) 
        : ticker(t), price(px), isBelowMA(belowMA), nSDev(ns), ma(a)
    {}

    std::string ticker;
    double      price;
    bool        isBelowMA;  // Is current price below Moving Average?
    double      nSDev;      // number of std dev's off Moving Average
    double      ma;
};

class TADataListener
{
public:
	virtual void addDataItem(const TADataItem& data) = 0;
};

typedef TADataListener* TADataListenerPtr;
