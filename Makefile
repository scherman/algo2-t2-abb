CXXFLAGS = -g -Wall

SOURCES = tests.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = tests

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
