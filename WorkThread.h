#pragma once

#include "TSQueue.h"

#include <thread>
#include <functional>
#include <memory>

typedef std::function<bool()> task_t;
typedef std::shared_ptr<TSQueue<task_t>> TaskQPtr;

inline bool exitThread()
{
    return true;
}

class WorkThread
{
public:
    WorkThread(TaskQPtr& taskQ)
        :   myThread(new std::thread(std::bind(&WorkThread::workLoop, taskQ))),
            myTaskQ(taskQ)
    {}

    ~WorkThread() {}

    static void workLoop(TaskQPtr& q)
    {
        TaskQPtr taskQ = q;
        task_t task;
        while (taskQ->pop(task))
        {
            if (task()) break;
        }
    }

	/*void sync() {
		myThread->join();
	}*/

    void exit()
    {
        myTaskQ->push(exitThread);
        myThread->join();
    }

private:
    std::shared_ptr<std::thread> myThread;
    TaskQPtr myTaskQ;

    WorkThread(const WorkThread&) = delete;
    WorkThread& operator=(const WorkThread&) = delete;
};

typedef std::shared_ptr<WorkThread> WorkThreadPtr;

// usage example
/*
#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
#include <conio.h>
#include "functions.h"

#include "TSQueue.h"        //************************
#include "WorkThread.h"     //************************

using namespace std;

int main() {

	fstream marketData("Sample.txt");
	int input, response, inputDay, input2, counter = 1;
	deque<double> data;

	cout << "Choose your method: " << "\n" << "1) Data from the last x days." << "\n" << "2) Data for x days from day y." << "\n";
	cin >> response;
	if (response == 1) {
		cout << "I want data from the last _ days: " << "\n";
		cin >> input;
	}
	if (response == 2) {
		cout << "I want data starting from day: " << "\n";
		cin >> inputDay;
		cout << "for _ days: " << "\n";
		cin >> input2;
	}

    TaskQPtr taskQ = std::make_shared<TSQueue<task_t>>();           //************************
    WorkThread wThread(taskQ);                                      //************************

	while (true) {
		if (_kbhit()) {
			break;
		}
		else {
			if (response == 1) {
				//analyzeLast(marketData, input, data);
                taskQ->push(std::bind(&analyzeLast, &marketData, input, data));                     //************************
				//input++; 
			}
			if (response == 2) {
				//analyzePast(marketData, input2, inputDay, data, counter);
                taskQ->push(std::bind(analyzePast, &marketData, input2, inputDay, data, counter));  //************************
				counter++;
			}
		}
	}

	marketData.close();
	system("pause");
	return 0;
}
*/