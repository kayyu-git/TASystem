#pragma once

#include "WorkThread.h"
#include "ThreadSafeCout.h"
#include "COutput.h"
#include "DataService.h"
#include "TADataListener.h"

#include <deque>
#include <vector>
#include <cmath>

class MAsDevCalculator : public DataListener
{
public:
    MAsDevCalculator(const std::string& ticker, int lookback, COutput& coutput, DataService& ds) 
        : myTicker(ticker), myCoutput(coutput), myLookBack(lookback), myDataService(ds)
    {
        myTaskQ = std::make_shared<TSQueue<task_t>>();
        myThread = std::make_shared<WorkThread>(myTaskQ);
		myDataService.registerListener(this);
    }

    ~MAsDevCalculator()
    {
    }

	/*void sync() {
		myThread->sync();
	}*/

    void exit()
    {
        myThread->exit();
    }

    void addDataItem(const double data);

	void changeSettings(const std::string& settings);

    void registerListener(TADataListenerPtr l)
    {
        myListeners.push_back(l);
    }


private:
    size_t              myLookBack;     // number of data periods for calculation

    std::deque<double>  myRawData;

    WorkThreadPtr       myThread;
    TaskQPtr            myTaskQ;

	std::string mySettings;
    std::string myTicker;

	double myLastMA = NAN;
	double myLastSDev = NAN;

	COutput& myCoutput;
	DataService& myDataService;

    std::vector<TADataListenerPtr> myListeners;

    bool calculate(std::deque<double>& data);

	bool doChangeSettings(const std::string& settings);
};
