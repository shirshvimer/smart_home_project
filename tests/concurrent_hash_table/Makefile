#safe hash table makefile
CXX = g++
CC = $(CXX)

CPPFLAGS = -I$(INC_DIR) -I$(INL_DIR)
CPPFLAGS += -MMD -MP -DDEBUG
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++17
CXXFLAGS+= -Wall -pedantic
CXXFLAGS+= -Werror
CXXFLAGS+= -g3

LDFLAGS = 
LDLIBS = -pthread

INL_DIR = ../../inc/inl
INC_DIR = ../../inc
SRC_DIR = ../../src

TARGET = utest
OBJS = utest.o 

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
