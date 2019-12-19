#pragma once

#include "WorkThread.h"
#include "ThreadSafeCout.h"

class COutput
{
public:
    COutput() 
    {
        myTaskQ = std::make_shared<TSQueue<task_t>>();
        myThread = std::make_shared<WorkThread>(myTaskQ);
    }

    ~COutput()
    {
    }

	/*void sync() {
		myThread->sync();
	}*/

    void exit()
    {
        myThread->exit();
    }

    void addDataItem(const std::string& text);

private:

    WorkThreadPtr       myThread;
    TaskQPtr            myTaskQ;

    bool display(const std::string& text);
};
