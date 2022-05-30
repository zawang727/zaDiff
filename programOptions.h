#include <iostream>
#include <studio.h>

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
	Solver solver = 1;
private:
	programOptions() = default;
	~programOptions() = default;
}