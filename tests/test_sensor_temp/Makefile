#thread pool makefile
CXX = g++
CC = $(CXX)

CPPFLAGS = -I$(INC_DIR) -I$(INL_DIR) -DTEST_SPRINKLER
CPPFLAGS += -MMD -MP
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++17
CXXFLAGS+= -Wall -pedantic
CXXFLAGS+= -Werror
CXXFLAGS+= -g3

LDFLAGS =
LDLIBS = -pthread -L../../library -lagents

INL_DIR = ../../inc/inl
INC_DIR = ../../inc
SERVER_DIR = ../../src/server
PROTOCOL_DIR = ../../src/protocol
CLIENT_DIR = ../../src/client

TARGET = utest_client
OBJS = utest_client.o $(CLIENT_DIR)/sensor_base.o $(CLIENT_DIR)/sensor_temperature.o $(SERVER_DIR)/tcp_client_socket.o $(SERVER_DIR)/threads_semaphore.o $(PROTOCOL_DIR)/protocol.o
OBJS += $(SERVER_DIR)/threads_thread_pool.o $(SERVER_DIR)/agent_manager.o $(SERVER_DIR)/events_publisher.o $(SERVER_DIR)/server_app.o 
OBJS += $(SERVER_DIR)/tcp_event_handler.o $(SERVER_DIR)/tcp_selector.o $(SERVER_DIR)/tcp_server_socket.o $(SERVER_DIR)/threads_act_for_threads_pool.o $(SERVER_DIR)/agent_loader.o $(SERVER_DIR)/proxy_events_publisher.o 
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

# LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../library/ 
# export LD_LIBRARY_PATH 

-include $(DEPENDS)