#include <iostream>

enum solverEnum
{
	solverEnumDefault = 0,
	solverEnumByLine = 1,
	solverHuntSzymanskiAlgorithm = 2
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
	float sameLineFilter = 0.5; // 0~1
	size_t lineDiffMaxChar = 100;
private:
	programOptions() = default;
	~programOptions() = default;
};