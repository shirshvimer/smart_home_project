#thread pool makefile
CXX = g++
CC = $(CXX)

CPPFLAGS = -I$(INC_DIR) -I$(INL_DIR)
CPPFLAGS += -MMD -MP
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++17
CXXFLAGS+= -Wall -pedantic
CXXFLAGS+= -Werror
CXXFLAGS+= -g3

LDFLAGS =
LDLIBS = -pthread


INL_DIR = ../../../inc/inl
INC_DIR = ../../../inc
SERVER_DIR = ../../../src/server
PROTOCOL_DIR = ../../../src/protocol
CLIENT_DIR = ../../../src/client

TARGET = main_client
OBJS = main_client.o $(CLIENT_DIR)/sensor_base.o $(CLIENT_DIR)/sensor_temperature.o $(CLIENT_DIR)/sensor_fire_detector.o $(CLIENT_DIR)/sensor_badge.o $(SERVER_DIR)/tcp_client_socket.o $(SERVER_DIR)/threads_semaphore.o $(PROTOCOL_DIR)/protocol.o

all: $(TARGET)

check: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJS)

vala: all
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)

.PHONY: all check clean

DEPENDS = $(OBJS:%.o=%.d)

-include $(DEPENDS)