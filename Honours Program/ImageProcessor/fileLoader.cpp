#include "stdafx.h"
#include "fileLoader.h"


namespace fileLoader
{
	char* loadFile(const char *fname, GLint &fSize) {
		int size;
		char * memblock;

		// file read based on example in cplusplus.com tutorial
		// ios::ate opens file at the end
		std::ifstream file(fname, std::ios::in | std::ios::binary | std::ios::ate);
		if (file.is_open()) {
			size = (int)file.tellg(); // get location of file pointer i.e. file size
			fSize = (GLint)size;
			memblock = new char[size];
			file.seekg(0, std::ios::beg);
			file.read(memblock, size);
			file.close();
			std::cout << "file " << fname << " loaded" << std::endl;
		}
		else {
			std::cout << "Unable to open file " << fname << std::endl;
			fSize = 0;
			// should ideally set a flag or use exception handling
			// so that calling function can decide what to do now
			return nullptr;
		}
		return memblock;
	}





float* loadHeightMatrix(int dataCount, std::string heightFile)
	{
		std::ifstream fileIn;
		fileIn.open(heightFile);
	
		if (!fileIn)
		{
			std::cout << "Error: File didnt open" << std::endl;
			return nullptr;
		}
			
		float dataSize = dataCount * sizeof(float);
		float* heightVal;
		heightVal = (float *)malloc(dataSize);

		std::string heightString;
		long double extractedVal;

				
			for (int i = 0; i < dataCount; i++)
			{
				getline(fileIn, heightString, ' ');				
				extractedVal = atof(heightString.c_str());
				heightVal[i] = extractedVal;// *10;
				
			}			
	


	

		return heightVal;

		

	}
}