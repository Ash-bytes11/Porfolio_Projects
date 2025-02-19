CXX = g++
CXXFLAGS = -Wall -g

proj5: MoviePlayer.o Movie.o proj5.cpp Queue.cpp
	$(CXX) $(CXXFLAGS) MoviePlayer.o Movie.o Queue.cpp proj5.cpp -o proj5

MoviePlayer.o: MoviePlayer.cpp  MoviePlayer.h Movie.o Queue.cpp
	$(CXX) $(CXXFLAGS) -c MoviePlayer.cpp

Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c Movie.cpp

Queue.o: Queue.cpp
	$(CXX) $(CXXFLAGS) -c Queue.cpp

run:
	./proj5 proj5_movies.txt

val:
	valgrind ./proj5 proj5_movies.txt

##Use this to clean out the directory
clean: 
	rm *~
	rm *.o

##Use this to test just the Queue
qtest: Queue.o queue_test.cpp
	$(CXX) $(CXXFLAGS) Queue.o queue_test.cpp -o qtest

##Use this to valgrind the Queue tests
qtest2:
	valgrind ./qtest

##Use this to debug the whole project
debug1:
	gdb gdbarg1 --args ./proj5 proj5_movies.txt
