#pragma once

#include "WorkThread.h"
#include "COutput.h"
#include "ThreadSafeCout.h"
#include "DataService.h"

#include <deque>

class EMACalculator : public DataListener
{
public:
	EMACalculator(int lookback, COutput& coutput, DataService& ds) : myCoutput(coutput), myLookBack(lookback), myDataService(ds)
	{
		myTaskQ = std::make_shared<TSQueue<task_t>>();
		myThread = std::make_shared<WorkThread>(myTaskQ);
		myDataService.registerListener(this);
	}

	~EMACalculator()
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

private:
	size_t              myLookBack;     

	std::deque<double>  myRawData;

	WorkThreadPtr       myThread;
	TaskQPtr            myTaskQ;

	int counter = 0;
	double prevEMA;

	COutput& myCoutput;
	DataService& myDataService;

	bool calculate(std::deque<double>& data);
};
