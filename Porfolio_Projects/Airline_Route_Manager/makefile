CXX = g++
CXXFLAGS = -Wall -g
IODIR = ../../proj3_IO/

proj3: Route.o Airport.o Navigator.o proj3.cpp 
	$(CXX) $(CXXFLAGS) Route.o Airport.o Navigator.o proj3.cpp -o proj3

Navigator.o: Airport.o Route.o Navigator.h Navigator.cpp
	$(CXX) $(CXXFLAGS) -c Navigator.cpp

Route.o: Airport.o Route.h Route.cpp
	$(CXX) $(CXXFLAGS) -c Route.cpp

Airport.o: Airport.h Airport.cpp
	$(CXX) $(CXXFLAGS) -c Airport.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3 proj3_data.txt

run1:
	./proj3 proj3_data.txt

val1:
	valgrind ./proj3 proj3_data.txt
