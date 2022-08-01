#include "File.h"
#include <filesystem>
#include <fstream>

namespace neu 
{
	void SetFilePath(const std::string& pathname)
	{
		//right-click on engine and change to c++17
		std::filesystem::current_path(pathname);
	}
	
	std::string GetFilePath()
	{
		return std::filesystem::current_path().string();
	}

	bool FileExists(const std::string& pathname)
	{
		return std::filesystem::exists(pathname);
	}

	bool GetFileSize(const std::string& pathname, size_t& size)
	{
		if (!FileExists(pathname)) return false;
		size = std::filesystem::file_size(pathname);
		
		return true;
	}

	bool ReadFile(const std::string& pathname, std::string& buffer)
	{
		if (!FileExists(pathname)) return false;

		//get file size and set buffer size
		size_t size;
		GetFileSize(pathname, size);
		buffer.resize(size);

		std::ifstream fstream(pathname);
		fstream.read(buffer.data(), size);
		fstream.close();

		return true;
	}

}
