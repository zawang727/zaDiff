#include <iostream>

enum Solver 
{ 
byLine = 1,
sameLineGreedy = 2,
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
	Solver solver = byLine;
private:
	programOptions() = default;
	~programOptions() = default;
};