cc=cc


exe=fin

all:compile

compile:
	cc -Wall -o $(exe) bezwithsdl.c display.c -lm -lSDL2 -lGL
run:$(exe)
	./$(exe)
compilerun:compile run
	
clean:
	rm -v $(exe)

