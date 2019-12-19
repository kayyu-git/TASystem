#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "MAsDevCalculator.h"
#include "EMACalculator.h"
#include "COutput.h"
#include "DataService.h"
#include "Analyzer.h"

using namespace std;

int main() {

	//fstream marketData("Sample.txt");
    int lookback;

	cout << "Lookback days: " << "\n";
	cin >> lookback;

	std::string fn("SP500.txt");
    std::string ticker("SP500");
	DataService bigData(fn);
	COutput consoleOut;
    MAsDevCalculator calculator(ticker, lookback, consoleOut, bigData);
	EMACalculator eCalculator(lookback, consoleOut, bigData);
    Analyzer analyzer(consoleOut, calculator);

	bigData.retrieveData();

   /* while (!marketData.eof())
    {
        string line;
        getline(marketData, line);
        calculator.addDataItem(stod(line));
		eCalculator.addDataItem(stod(line));
		//calculator.sync();
		//eCalculator.sync();
    }*/

	eCalculator.exit();
    calculator.exit();
    analyzer.exit();
    consoleOut.exit();

	//marketData.close();

	system("pause");
	return 0;
}