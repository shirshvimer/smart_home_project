#thread pool makefile
CXX = g++
CC = $(CXX)

CPPFLAGS = -I$(INC_DIR) -I$(INL_DIR)
CPPFLAGS += -MMD -MP
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++17
CXXFLAGS+= -fPIC -Wall -pedantic
CXXFLAGS+= -Werror
CXXFLAGS+= -g3

LDFLAGS =
LDLIBS = -pthread


INL_DIR = ../inc/inl
INC_DIR = ../inc
SERVER_DIR = ../library

TARGET = lib.so
OBJS = $(SERVER_DIR)/agent_aircondition.o $(SERVER_DIR)/agent_factory.o $(SERVER_DIR)/agent_fire_detector_sensor.o $(SERVER_DIR)/agent_generator.o $(SERVER_DIR)/agent_sprinkler.o $(SERVER_DIR)/agent_tempature_sensor.o
OBJS += $(SERVER_DIR)/agent_badge_sensor.o $(SERVER_DIR)/agent_door.o
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


#gcc -shared -o libagents.so agent_aircondition.o agent_factory.o agent_fire_detector_sensor.o agent_generator.o agent_sprinkler.o agent_tempature_sensor.o agent_badge_sensor.o agent_door.o
