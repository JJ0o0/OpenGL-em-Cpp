CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra
LDFLAGS = -Llib

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJECT_DIR = $(BUILD_DIR)/obj
GLAD_SRC = $(INCLUDE_DIR)/glad/glad.c
GLAD_OBJ = $(OBJECT_DIR)/glad.o

TARGET = $(BUILD_DIR)/desafio_3

ifeq ($(OS),Windows_NT)
	MKDIR_CMD = if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	MKDIR_O_CMD = if not exist "$(OBJECT_DIR)" mkdir "$(OBJECT_DIR)"
    RM_CMD = if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	RM_O_CMD = if exist "$(OBJECT_DIR)" rmdir /s /q "$(OBJECT_DIR)"
	LDLIBS = -lglfw3 -lopengl32 -lgdi32
else
	MKDIR_CMD = mkdir -p $(BUILD_DIR)
	MKDIR_O_CMD = mkdir -p $(OBJECT_DIR)
    RM_CMD = rm -rf $(BUILD_DIR)
	RM_O_CMD = rm -rf $(OBJECT_DIR)
	LDLIBS = -lglfw -lGL -ldl
endif

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(GLAD_SRC)
OBJECTS = $(patsubst %.cpp,$(OBJECT_DIR)/%.o,$(notdir $(filter %.cpp,$(SOURCES)))) $(GLAD_OBJ)

all: $(BUILD_DIR) $(OBJECT_DIR) $(TARGET) clean

$(BUILD_DIR):
	$(MKDIR_CMD)

$(OBJECT_DIR):
	$(MKDIR_O_CMD)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDLIBS)

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJECT_DIR)/glad.o: $(GLAD_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

rebuild: distclean all

clean:
	$(RM_O_CMD)

distclean:
	$(RM_CMD)

.PHONY: all distclean rebuild