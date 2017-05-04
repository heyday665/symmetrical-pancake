#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

class MODEL
{
    public:
        MODEL();
        ~MODEL();
        bool loadModel(std::string);
        bool saveModel(std::string);//format is ply
        bool formatSupported(std::string);//use map fill at start check against
        bool loadEmptyModel();
        bool render(glm::mat4 View,glm::mat4 Projection,struct ENGINEDATA &);
        void rotate(glm::vec4);
        void transform(glm::vec4);
        void scale(glm::vec4);
        std::string getFilePath();
    private:
        void sceneToVertlist();
        const struct aiScene *scene;
        std::string fileName,filePath;
        unsigned int IFlags,EFlags;
        GLuint vertexBuffer,colorBuffer;
        glm::mat4 ModelMatrix;
        std::vector<glm::vec3> vertlist;
};

#endif