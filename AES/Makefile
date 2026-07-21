CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = aes

SRCS = main.cpp aes.cpp

HDRS = aes.hpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HDRS)	
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
