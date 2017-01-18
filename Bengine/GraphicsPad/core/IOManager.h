#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <vector>

class IOManager
{
public:
	static bool ReadFileToBuffer(std::string filePath, std::vector<char> &buffer);
};

#endif