run: lab2.cpp LoadShaders1.cpp
	g++ lab2.cpp  LoadShaders1.cpp -lglut -lGLU -lGL -lGLEW -g 
	
clean: 
	rm -f *.out *~ run
	
