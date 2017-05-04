#ifndef BEZMAKER_H
#define BEZMAKER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glm/glm.hpp>

class BEZMAKER
{
	public:
		BEZMAKER();
		~BEZMAKER();
		void setRand();
		void genControlPoints();
		void genPatchPoints();
		void setStep(float);
		glm::vec3** getBez();
		
		
	private:
		glm::vec3 **bez;
		glm::vec3 **stepPoints;	
		float step;
		time_t seed;




};


#endif
