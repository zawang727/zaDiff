#include <iostream>

enum solverEnum
{
	solverEnumDefault = 0,
	solverEnumByLine = 1,
	solverGreedy1 = 2,
	solverHuntSzymanski = 3
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
	int debugMsgLevel = 5;
	solverEnum solver = solverEnumDefault;
	diffPrinterEnum diffPrinter = diffPrinterEnumDefault;

	//solverHuntSzymanskiAlgorithm
	float sameLineFilter = 0.9; // 0~1
	float identicalLineFilter = 0.4; // 0~1
	size_t lineDiffMaxChar = 100;

private:
	programOptions() = default;
	~programOptions() = default;
};