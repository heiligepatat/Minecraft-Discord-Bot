# Compiler and flags
CXX = g++
CXXFLAGS = -Wall

# Files
SRCS = main.cpp discordmessage.cpp playercount.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = serverbot

compile_bot: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp playercount.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

discordmessage.o: discordmessage.cpp discordmessage.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

playercount.o: playercount.cpp playercount.hpp discordmessage.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
