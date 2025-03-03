all: simulation clean

simulation: main.o state.o simulation.o render.o
	g++ main.o state.o simulation.o render.o -o simulation -lGL -lGLU -lglut

main.o: main.cpp
	g++ -c main.cpp

state.o: state.cpp state.hpp
	g++ -c state.cpp

simulation.o: simulation.cpp simulation.hpp
	g++ -c simulation.cpp

render.o: render.cpp render.hpp
	g++ -c render.cpp

clean:
	rm -rf *.o
