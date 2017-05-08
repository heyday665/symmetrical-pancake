#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include "bezMaker.h"

class MODEL
{
    public:
        MODEL();
        ~MODEL();
        bool loadModel(std::string);
        bool saveModel(std::string);//format is ply
        bool formatSupported(std::string);//use map fill at start check against
        bool loadEmptyModel();
        bool render(glm::mat4 View, glm::mat4 Projection, struct ENGINEDATA &);
        void rotate(glm::vec4);
        void transform(glm::vec4);
        void scale(glm::vec4);
        void updatePatch(float);
        glm::vec3** fuckingBezShit;
        std::string getFilePath();
        std::string getBezPath();
        void setBezPath(std::string);

    private:
        void sceneToVertlist();
        const struct aiScene *scene;
        std::string fileName, filePath, bezPath;
        unsigned int IFlags, EFlags;
        GLuint vertexBuffer, colorBuffer;
        BEZMAKER bezList;
        glm::mat4 ModelMatrix;
        std::vector<glm::vec3> vertlist;
        int numStepPoints;
        void bezToPly();
};

#endif
