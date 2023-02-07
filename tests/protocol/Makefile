CXX = g++
CC = $(CXX)

CPPFLAGS = -I$(INC_DIR)
CPPFLAGS += -MMD -MP 
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++17
CXXFLAGS+= -Wall -pedantic
CXXFLAGS+= -Werror
CXXFLAGS+= -g3

LDFLAGS =
LDLIBS =

SRC_DIR = ../../src/protocol
INC_DIR = ../../inc

TARGET = protocol_tests
OBJS = protocol_tests.o $(SRC_DIR)/protocol.o 
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
