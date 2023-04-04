CXX = g++
CXXFLAGS = -std=c++23 -Wall -c
LXXFLAGS = -std=c++23
OBJECTS = main.o matrix.o unit_test.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET) -lgtest -lgtest_main -pthread
main.o: src/main.cpp src/unit_test.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp
matrix.o:src/matrix.cpp include/matrix.h
	$(CXX) $(CXXFLAGS) src/matrix.cpp
unit_test.o: src/unit_test.cpp
	$(CXX) $(CXXFLAGS) src/unit_test.cpp
clean:
	rm -f $(TARGET) $(OBJECTS)