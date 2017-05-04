//Basic C/C++ includes
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

//GLEW include
#include <GL/glew.h>

//GLFW for quality of life
#include <GLFW/glfw3.h>

//GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Global defs
GLFWwindow* window;
GLuint VertexArrayID;
GLuint VertexBuffer;
GLuint colorBuffer;
GLuint programID;
GLuint MatrixID;

//MVP Matrix
glm::mat4 MVP;
glm::mat4 Model;
glm::mat4 View;
glm::mat4 Proj;

//Test Objects that DEFINITELY work
//Cube and colors
static const GLfloat g_vertex_buffer_data_cube[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f
};

static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

glm::mat3 screenCoOrdNormal(int x, int y);

void createMVPMatrix();

void myCustomInit();

GLuint LoadShaders();

int main(int argc, char** argv){
	// Call Init
	myCustomInit();

	// Load VS and FS
	programID = LoadShaders();

	// Create the damn mvp... 
	// I was forgetting to do this
	// wondering why the mvp wasnt
	// working...
	createMVPMatrix();

	// Do the thing for the shader
	MatrixID = glGetUniformLocation(programID, "MVP");

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f,0.0f,0.3f,0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//Useful, but worse performance
	//glEnable(GL_CULL_FACE);

 	double lastTime = glfwGetTime();
 	int nbFrames = 0;

	do{
	    //
	    // EVERYTHING HAPPENS BELOW
	    //

	    //Ms to draw frame
	    double currentTime = glfwGetTime();
	    nbFrames++;
	    if ( currentTime - lastTime >= 1.0 ){ // If last print was more than 1 sec ago
	        // printf and reset timer
	        printf("%f ms/frame\n", 1000.0/double(nbFrames));
	        nbFrames = 0;
	        lastTime += 1.0;

	       	double xpos, ypos;
	    	glfwGetCursorPos(window, &xpos, &ypos);

	    	//printf("x: %f\ny: %f\n", xpos, ypos);

	    	glm::mat3 cursorPoints;
	    	if (xpos>=0 && ypos>=0){
	    		cursorPoints = screenCoOrdNormal(xpos, ypos);
	    	}

	    	float matrixtempthing[3][2];
	    	for (int j = 0; j < 3; j++)
	    	{
				for (int y = 0; y < 2; y++){
					matrixtempthing[j][y] = 0;
					matrixtempthing[j][y] = cursorPoints[j][y];
				}
	    	}
	    	printf("Point: %.4f %.4f %.4f\n", matrixtempthing[0][0], matrixtempthing[1][0], matrixtempthing[2][0]);
			printf("Point: %.4f %.4f %.4f\n", matrixtempthing[0][1], matrixtempthing[1][1], matrixtempthing[2][1]);
	    }

	    //Some setup
	   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    glUseProgram(programID);

	    //Use MVP martrix
	    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	    //AttribBuff: Verts
	    glEnableVertexAttribArray(0);
	    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*) 0); //attribute, size, type, normal?, stride, offset

	    //AttribBuff: Color
	    glEnableVertexAttribArray(1);
	    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*) 0); //attribute, size, type, normal?, stride, offset

	    //Draw Triangle
	    //glDrawArrays(GL_TRIANGLES, 0, 3); //Start @0, 3 total verts
	    //Draw Cube
	    glDrawArrays(GL_TRIANGLES, 0, 12*3); //0 -> 36 total verts

	    glDisableVertexAttribArray(0);
	    glDisableVertexAttribArray(1);

	    //
	    // EVERYTHING HAPPENS ABOVE
	    //

	    // Swap the damn buffers
	    glfwSwapBuffers(window);
	    glfwPollEvents();

	}
	// Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
}

void createMVPMatrix(){
	Proj = glm::perspective(glm::radians(45.0f), 1600.0f/900.0f, 0.1f, 100.0f);
	View = glm::lookAt(glm::vec3(0,0,-5), glm::vec3(0,0,0), glm::vec3(0,1,0));
	Model = glm::mat4(1.0f);

	MVP = Proj * View * Model;
}

void myCustomInit(){
	// GLFW
	if (!glfwInit()) {cerr<< "Shit broke fam: 1"; exit(-10);}

	// Tell GLFW some stuff
	glfwWindowHint(GLFW_SAMPLES, 4); //4x AA
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL x.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //OpenGL x.x
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //New OpenGL vs 2/1

	// Open window + OpenGL context
	window = glfwCreateWindow(1600,900,"Object Viewer", NULL,NULL);
	if (window == NULL) {cerr<< "Shit broke fam: 2"; glfwTerminate(); exit(-9);}
	glfwMakeContextCurrent(window); // Tells GLEW to be alive
	glewExperimental=true; // Required with newer OpenGL
	if (glewInit() != GLEW_OK) {cerr<< "Shit broke fam: 3"; exit(-8);}

	// Gen/Bind VAO
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Gen/Bind VB
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	//Use for Triangle
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_triangle), g_vertex_buffer_data_triangle, GL_STATIC_DRAW);
	//Use for Cube
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_cube), g_vertex_buffer_data_cube, GL_STATIC_DRAW);

	// Gen/Bind ColorBuf
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

GLuint LoadShaders(){
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream("vertex.vs", std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open 'vertex.vs'. Are you in the right directory ? Don't forget to read the FAQ !\n");
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream("fragment.fs", std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling vertex shader\n");
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling fragment shader\n");
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

glm::mat3 screenCoOrdNormal(int x, int y){
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	glm::vec4 viewPorto = glm::vec4(viewport[0],viewport[1], viewport[2], viewport[3]);

	glm::vec3 far = glm::normalize(glm::unProject(glm::vec3(1600-x,900-y,0.0), View*Model, Proj, viewPorto));
	glm::vec3 near = glm::normalize(glm::unProject(glm::vec3(1600-x,900-y,1.0), View*Model, Proj, viewPorto));
	glm::mat3 ret = glm::mat3(far, near, glm::vec3(1));

	return ret;
	//printf("%d, %d, %d, %d\n", viewport[0],viewport[1], viewport[2], viewport[3]);
	//printf("%f \t| %f \t| %f\n", near[0], near[1], near[2]);
	//printf("%f \t| %f \t| %f\n", far[0], far[1], far[2]);
	//	glm::vec3 Direction = glm::vec3(near[0]-far[0], near[1]-far[1], near[2]-far[2]);
}