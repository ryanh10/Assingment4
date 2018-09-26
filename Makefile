# the compiler: g++ for c++
CC = g++ -pthread -std=c++11

# compiler flags:
# -g 	adds debugging information to the executable file
# -Wall	turns on most, but not all, compiler warnings
CFLAGS = -Wall -Wextra -Werror -g

# the build target executable:
TARGET = can_decoder

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
