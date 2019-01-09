#The C++ compiler
CXX = g++ -std=c++14

#Flags for debugging
CXXFLAGS = -g -Wall 

TARGET = cullclip


$(TARGET) : main.o Object.o Camera.o Placement.o triangle.o vecpt.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o Object.o Camera.o Placement.o triangle.o vecpt.o

main.o : main.cpp Object.h frsthelp.h Camera.h Placement.h triangle.h vecpt.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Object.o : Object.cpp Object.h Placement.h vecpt.h
	$(CXX) $(CXXFLAGS) -c Object.cpp

Camera.o : Camera.cpp Camera.h vecpt.h
	$(CXX) $(CXXFLAGS) -c Camera.cpp

Placement.o : Placement.cpp Placement.h vecpt.h
	$(CXX) $(CXXFLAGS) -c Placement.cpp

triangle.o : triangle.h triangle.cpp vecpt.h Object.h
	$(CXX) $(CXXFLAGS) -c triangle.cpp

vecpt.o : vecpt.h
	$(CXX) $(CXXFLAGS) -c vecpt.cpp

clean:
	rm cullclip *.o
