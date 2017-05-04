#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#include "/home/cooldylan/programing/Graphics/DisplayEngine2/model .h"

int main()
{
    std::string path("boxy2.ply");
    std::string outpath("output.ply");
    MODEL test;
    if(!test.loadModel(path))
    {
        std::cout << "error loading model" << std::endl;
        return -1;
    }
    std::cout << "model lodead" << std::endl;
    if(!test.saveModel(outpath))
    {
        std::cout << "error saving model" << std::endl;
        return -1;
    }
    std::cout << "model saved" << std::endl;

    test.formatSupported(path);

    test.formatSupported(std::string("this is text"));

}