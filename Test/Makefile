CXX = C:\ProgramowanieToolchain\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe
CC = C:\ProgramowanieToolchain\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe

CXXFLAGS = -std=gnu++11 -Wall
INCLUDES = \
-IFramework/googletest-master/googletest/ \
-IFramework/googletest-master/googletest/include \

LDFLAGS = 

TESTSOURCES_DIR = Framework/googletest-master/googletest/src

TESTSOURCES = \
$(TESTSOURCES_DIR)/gtest-all.cc \
$(TESTSOURCES_DIR)/gtest_main.cc \

SOURCES = \

NAME = FreeRTOS_UT

OUTPUT_DIR = Output\UT
OBJ_DIR = $(OUTPUT_DIR)\Obj

SRC = $(SOURCES) $(TESTSOURCES)

OBJECTS = \
$(addprefix $(OBJ_DIR)/, $(notdir $(filter %.o, $(SRC:.cpp=.o)))) \
$(addprefix $(OBJ_DIR)/, $(notdir $(filter %.o, $(SRC:.cc=.o))))

all: $(OUTPUT_DIR) $(NAME)
	@echo $(OBJECTS)

$(NAME): $(OBJECTS)
	$(CXX) -o $(OUTPUT_DIR)/$(NAME).exe $(OBJECTS)

$(OBJ_DIR)/%.o: Test/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

$(OBJ_DIR)/%.o: $(TESTSOURCES_DIR)/%.cc
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

$(OUTPUT_DIR):
	mkdir $(subst /, \\, $@)
	mkdir $(subst /, \\, $(OBJ_DIR))

clean:
ifneq ($(wildcard $(OUTPUT_DIR)/.*),)
	rmdir $(subst /, \\, $(OUTPUT_DIR)) /s /q
endif