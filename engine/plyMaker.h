#ifndef PLYMAKER_H
#define PLYMAKER_H

#include <string>
#include <vector>

#include "bezMaker.h"

class PLYMAKER
{
	public:
		PLYMAKER();
		~PLYMAKER();
		void bezToPly(glm::vec3);
		
	private:
		std::string outputPath;
		
};

#endif
