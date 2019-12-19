#pragma once

#include "WorkThread.h"
#include "COutput.h"
#include "MAsDevCalculator.h"

class Analyzer : public TADataListener
{
public:
    Analyzer(COutput& coutput, MAsDevCalculator& calculator) : myCoutput(coutput), myPnL(0.0)
    {
        myTaskQ = std::make_shared<TSQueue<task_t>>();
        myThread = std::make_shared<WorkThread>(myTaskQ);
        calculator.registerListener(this);
    }

    ~Analyzer()
    {
    }

    void exit()
    {
        myThread->exit();
    }

    void addDataItem(const TADataItem& data);

private:
    WorkThreadPtr       myThread;
    TaskQPtr            myTaskQ;

    COutput&            myCoutput;

    double              myPnL;

    bool calculate(const TADataItem& data);
};
