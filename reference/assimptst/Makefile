CCFLAGS = g++

Executable = assimp

SourceFiles = assimp.cpp

LinkerFlags = -lassimp

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
