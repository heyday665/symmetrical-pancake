#ifndef MODELREADER_H
#define MODELREADER_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

struct newply
{
	std::vector<glm::vec3> vertlist;
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;
};

typedef struct
{
	int a,s,d;
}triangleFace;

struct ply
{
  char* FileN;
  int Nvertes;
  int Nfaces;
  glm::vec3 *vertlist;
  triangleFace *facelist;
};

class MODELREADER
{
public:
  int readinply(struct ply*);
  int readinply(std::string,std::vector<glm::vec3> &);
  int normalizeModel(struct ply *);
  int plyToGlData(struct ply*, std::vector<glm::vec3> &);
protected:

private:
};


static MODELREADER modelreader;

#endif
