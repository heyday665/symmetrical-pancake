#include "bezMaker.h"

	BEZMAKER::BEZMAKER()
	{
		step = 0.2f;
		bez = new glm::vec3*[4];
		for(int i = 0; i < 4; ++i)
		{
			bez[i] = new glm::vec3[4];
		}
	}

	BEZMAKER::~BEZMAKER()
	{
		//frees
	}

	glm::vec3 ** BEZMAKER::getBez()
	{
		return bez;
	}

	int BEZMAKER::getNumStepPoints()
	{
		return numStepPoints;
	}
  
	void BEZMAKER::setRand()
	{
		seed = time(0);
		srand48(seed);
	}

	void BEZMAKER::setStep(float stp)
	{
		if(stp > 0.0f)
		{
			step = stp;
		}
	}

	void BEZMAKER::genControlPoints()
	{
		int i, j;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				bez[i][j].x = drand48() * 2 - 1;
				bez[i][j].y = drand48() * 2 - 1;
				bez[i][j].z = drand48() * 2 - 1;
			}
		}
	}
	
	void BEZMAKER::genPatchPoints()
	{
		float u, v,uu,uuu,vv,vvv;

			numStepPoints = (1/step) + 1;

			free(stepPoints);
			stepPoints = new glm::vec3*[numStepPoints];
			for(int i = 0; i < numStepPoints; i++)
			{
				stepPoints[i] = new glm::vec3[numStepPoints];
			}

			int row, col;
			row = col = 0;

			for(u = 0; u <= 1.0; u += step)
			{
				for(v = 0; v <= 1.0; v += step)
				{
					uu = (1.0 - u) * (1.0 - u);
					vv = (1.0 - v) * (1.0 - v);
					uuu = (1.0 - u) * (1.0 - u) * (1.0 - u);
					vvv = (1.0 - v) * (1.0 - v) * (1.0 - v);

					stepPoints[row][col].x = uuu * vvv * bez[0][0].x +
						  uuu * 3 * v * vv * bez[0][1].x +
						  uuu * 3 * (v * v) * (1.0-v) * bez[0][2].x +
						  uuu * (v * v * v) * bez[0][3].x +

						  3 * u * uu * vvv * bez[1][0].x +
				 	    3 * u * uu * 3 * v * vv * bez[1][1].x +
						  3 * u * uu * 3 * (v * v) * (1.0 - v) * bez[1][2].x +
						  3 * u * uu * (v * v * v) * bez[1][3].x +

						  3 * (u * u) * (1.0-u) * vvv * bez[2][0].x +
						  3 * (u * u) * (1.0-u) * 3 * v * vv * bez[2][1].x +
						  3 * (u * u) * (1.0-u) * 3 * (v * v) * (1.0 - v) * bez[2][2].x +
						  3 * (u * u) * (1.0-u) * 1.0 * (v * v * v) * 1.0 * bez[2][3].x +

						  (u * u * u) * vvv * bez[3][0].x +
						  (u * u * u) * 3 * v * vv * bez[3][1].x +
						  (u * u * u) * 3 * (v * v) * (1.0 - v) * bez[3][2].x +
						  (u * u * u) * (v * v * v) * bez[3][3].x;

					stepPoints[row][col].y = uuu * vvv * bez[0][0].y +
						  uuu * 3 * v * vv * bez[0][1].y +
						  uuu * 3 * (v * v) * (1.0-v) * bez[0][2].y +
						  uuu * (v * v * v) * bez[0][3].y +

						  3 * u * uu * vvv * bez[1][0].y +
				 	    3 * u * uu * 3 * v * vv * bez[1][1].y +
						  3 * u * uu * 3 * (v * v) * (1.0 - v) * bez[1][2].y +
						  3 * u * uu * (v * v * v) * bez[1][3].y +

						  3 * (u * u) * (1.0-u) * vvv * bez[2][0].y +
						  3 * (u * u) * (1.0-u) * 3 * v * vv * bez[2][1].y +
						  3 * (u * u) * (1.0-u) * 3 * (v * v) * (1.0 - v) * bez[2][2].y +
						  3 * (u * u) * (1.0-u) * (v * v * v) * bez[2][3].y +

						  (u * u * u) * vvv * bez[3][0].y +
						  (u * u * u) * 3 * v * vv * bez[3][1].y +
						  (u * u * u) * 3 * (v * v) * (1.0 - v) * bez[3][2].y +
						  (u * u * u) * (v * v * v) * bez[3][3].y;


					stepPoints[row][col].z = uuu * vvv * bez[0][0].z +
						  uuu * 3 * v * vv * bez[0][1].z +
						  uuu * 3 * (v * v) * (1.0-v) * bez[0][2].z +
						  uuu * (v * v * v) * bez[0][3].z +

						  3 * u * uu * vvv * bez[1][0].z +
				 	    3 * u * uu * 3 * v * vv * bez[1][1].z +
						  3 * u * uu * 3 * (v * v) * (1.0 - v) * bez[1][2].z +
						  3 * u * uu * (v * v * v) * bez[1][3].z +

						  3 * (u * u) * (1.0-u) * vvv * bez[2][0].z +
						  3 * (u * u) * (1.0-u) * 3 * v * vv * bez[2][1].z +
						  3 * (u * u) * (1.0-u) * 3 * (v * v) * (1.0 - v) * bez[2][2].z +
						  3 * (u * u) * (1.0-u) * (v * v * v) * bez[2][3].z +

						  (u * u * u) * vvv * bez[3][0].z +
						  (u * u * u) * 3 * v * vv * bez[3][1].z +
						  (u * u * u) * 3 * (v * v) * (1.0 - v) * bez[3][2].z +
						  (u * u * u) * (v * v * v) * bez[3][3].z;
						  col++;
				}
			printf("Row %d COl %d",row,col);
			row++;
			col = 0;
			}

	}

	
