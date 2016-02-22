#include "IOManager.h"

#include <fstream>

bool IOManager::ReadFileToBuffer(std::string filePath, std::vector<char> &buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	//Seek to end of file and get byte offset to determine size
	file.seekg(0, std::ios::end);

	//Get the file size
	int fileSize = file.tellg();

	//Return to beginning of file
	file.seekg(0, std::ios::beg);

	//Reduce the file size by header bytes if present
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read(&(buffer[0]), fileSize);
	file.close();

	return true;
}
