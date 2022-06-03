#include <iostream>

enum solverEnum
{
	solverEnumDefault = 0,
	solverEnumByLine = 1,
	solverEnumSameLineGreedy = 2
};
enum diffPrinterEnum
{ 
	diffPrinterEnumDefault = 0,
	diffPrinterEnumMerged = 1,
	diffPrinterEnumSingle = 2
};

class programOptions
{
public:
	static programOptions& getInstance()
	{
		static programOptions instance;
		return instance;
	}
	int debugMsgLevel = 1;
	solverEnum solver = solverEnumDefault;
	diffPrinterEnum diffPrinter = diffPrinterEnumDefault;

private:
	programOptions() = default;
	~programOptions() = default;
};