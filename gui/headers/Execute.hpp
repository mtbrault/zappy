/*
**
**
**
*/

#include <string.h>

class Execute
{
public:
	Execute(std::string command, char *const args[])
	{
		execv(command.c_str(), args);
	}
	~Execute() = default;
};