#pragma once
#include <string>
#include <fstream>

namespace FileSystem
{
	std::string ReadFile(const std::string& path)
	{
		std::ifstream MyReadFile(path);
		std::string fileContent = "";
		std::string allFile = "";

		while (getline(MyReadFile, fileContent))
		{
			allFile.append(fileContent + "\n");
		}

		MyReadFile.close();
		return allFile;
	}

	std::ofstream fileWriter;
	bool BeginWriteFile(const std::string path)
	{
		fileWriter = std::ofstream();
		fileWriter.open(path);

		return false;
	}

	bool WriteLine(const std::string line)
	{
		fileWriter << line.c_str();

		return true;
	}

	void EndWriteFile()
	{
		fileWriter.close();
	}

	bool DirectoryExists(const std::string path)
	{
		return false;
	}

	bool FileExists(const std::string path)
	{
		std::ifstream f(path.c_str());
		return f.good();
	}
}