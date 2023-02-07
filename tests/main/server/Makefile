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

# LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../library/ 
# export LD_LIBRARY_PATH 

LDFLAGS =
LDLIBS = -pthread -L../../../library -lagents

SRC_DIR = ../../../src/server
INC_DIR = ../../../inc
INL_DIR = ../../../inc/inl
PROT_DIR = ../../../src/protocol

TARGET = main_server 
OBJS = main_server.o $(SRC_DIR)/threads_semaphore.o $(SRC_DIR)/threads_thread_pool.o $(SRC_DIR)/agent_manager.o $(SRC_DIR)/events_publisher.o $(SRC_DIR)/server_app.o $(SRC_DIR)/tcp_client_socket.o 
OBJS += $(SRC_DIR)/tcp_event_handler.o $(SRC_DIR)/tcp_selector.o $(SRC_DIR)/tcp_server_socket.o $(SRC_DIR)/threads_act_for_threads_pool.o $(SRC_DIR)/agent_loader.o $(SRC_DIR)/proxy_events_publisher.o $(PROT_DIR)/protocol.o $(SRC_DIR)/save_data_ostream.o $(SRC_DIR)/save_data_db.o
all: $(TARGET) 

check: $(TARGET)
	./$(TARGET) -v 
$(TARGET): $(OBJS) 

vala: all
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

#utest.o: $(INC_DIR)/sm_code.hpp $(INC_DIR)/sm_compiler.hpp

clean: 
	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)

.PHONY: all check clean DEPENDS = $(OBJS:%.o=%.d)

DEPENDS = $(OBJS:%.o=%.d)
 
-include $(DEPENDS) 
