#include "bezMaker.h"

	BEZMAKER::BEZMAKER()
	{
		bez = new glm::vec3*[4];
		for(int i = 0; i < 4; ++i){
		  bez[i] = new glm::vec3[4];
		}
	}
  
  void BEZMAKER::setRand()
  {
  	seed = time(0);
  	srand48(seed);
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
		int i, numStepPoints;
		float u, v;

			//numStepPoints = (1/step) + 1;
			//printf("%d\n", numStepPoints);

			points stepPoints[numStepPoints][numStepPoints];
			int row, col;
			row = col = 0;

			for(u = 0; u <= 1.0; u += step)
			{
				for(v = 0; v <= 1.0; v += step)
				{
					float uu = (1.0 - u) * (1.0 - u);
					float vv = (1.0 - v) * (1.0 - v);
					float uuu = (1.0 - u) * (1.0 - u) * (1.0 - u);
					float vvv = (1.0 - v) * (1.0 - v) * (1.0 - v);

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
				}
			row++;
			col = 0;
			}

			/*for(int i = 0;i < numStepPoints;i++)
			{
				for(int j = 0;j < numStepPoints;j++)
				{	
					glVertex3f(stepPoints[i][j].x,stepPoints[i][j].y,stepPoints[i][j].z);

					if(stepPoints[i][j].x >= 1 || stepPoints[i][j].x <= -1)
					{
						printf("X i:%d j:%d\n",i,j);
					}
					if(stepPoints[i][j].y >= 1 || stepPoints[i][j].y <= -1)
					{
						printf("Y i:%d j:%d\n",i,j);
					}
					if(stepPoints[i][j].z >= 1 || stepPoints[i][j].z <= -1)
					{
						printf("Z i:%d j:%d\n",i,j);
					}

					printf("X:%f Y:%f Z:%f\n",stepPoints[i][j].x,stepPoints[i][j].y,stepPoints[i][j].z);
				}		
			}*/

			for(int i = 0;i<4;i++)
			{
				for(int j = 0;j<4;j++)
				{
					glVertex3f(bez[i][j].x,bez[i][j].y,bez[i][j].z);
					printf("point: i:%d j:%d\n",i,j);
				}
			}
	}
