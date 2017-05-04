CCFLAGS = g++

Executable = displayengine2

SourceFiles = start.cpp modelreader.cpp settings.cpp keyboard.cpp mouse.cpp model.cpp

LinkerFlags = -lm -lSDL2 -lGL -lGLU -lGLEW -lassimp

Info = "PROJECT: \nAUTHER: Dylan Gebel, \nCONTACTINFO: Dylanfoxx@optonline.net \nDEPENDENCIES: \n"

all:compile

Debug: CCFLAGS += -g
Debug: compile

compile: CCFLAGS += -o
compile:
	$(CCFLAGS) $(Executable) $(SourceFiles) $(LinkerFlags)
Info:
	@echo $(Info)
clean:
	rm -v $(Executable)
