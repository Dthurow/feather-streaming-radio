DIR := ${CURDIR}
SKETCH = $(DIR)/src/internet_streaming.cpp
BUILD_DIR = $(DIR)/build
BOARD = huzzah
LIBS = $(HOME)/.arduino15/packages/esp8266/hardware/esp8266/2.7.4/libraries $(HOME)/Arduino/libraries 
EXCLUDE_DIRS = test
include $(DIR)/makeEspArduino/makeEspArduino.mk


#Tool Definitions
CC=g++
CFLAGS=-I. -I$(PATHU) -I$(PATHI) -I$(PATHS) -I$(PATHT)/fakes -I$(PATHT)/header_overrides -DTEST
TARGET_EXTENSION=.out

#Path Definitions
PATHU = test/unity/
PATHS = src/
PATHT = test/
PATHI = inc/
PATHB = build/

#determine all our source files
SRCUNITY = $(PATHU)unity.c
#testable source files here
SRCSRC = $(PATHS)rssReader.cpp
SRCTEST = $(wildcard $(PATHT)*.cpp)
SRCTESTSUPPORTERS =  $(wildcard $(PATHT)fakes/*.cpp)


OBJUNITY = $(patsubst $(PATHU)%.c,$(PATHB)%.o,$(SRCUNITY))
OBJSRC = $(patsubst $(PATHS)%.cpp,$(PATHB)%.o,$(SRCSRC))
OBJTESTSUPPORTERS = $(patsubst $(PATHT)%.cpp,$(PATHB)%.o,$(SRCTESTSUPPORTERS))
ALLTESTSUPPORTINGOBJ = $(OBJUNITY) $(OBJSRC) $(OBJTESTSUPPORTERS)
OBJTESTS = $(patsubst $(PATHT)%.cpp,$(PATHB)%.o,$(SRCTEST))

#Other files we care about
DEP = $(PATHU)unity.h $(PATHU)unity_internals.h 
TARGETS = $(patsubst $(PATHT)%.cpp,$(PATHB)%$(TARGET_EXTENSION),$(SRCTEST))


test: $(PATHB) $(PATHB)fakes $(TARGETS)
	echo $(TARGETS)
	echo "made tests"
	for i in $(TARGETS); do \
            $$i; \
        done

#make sure directory exists
$(PATHB):
	 mkdir -p $(PATHB)

#make sure directory exists
$(PATHB)fakes:
	mkdir -p $(PATHB)fakes

$(TARGETS): $(OBJTESTS) $(ALLTESTSUPPORTINGOBJ)
	echo "linking for $@"
	$(CC) -o $@ $(patsubst $(PATHB)%.out,$(PATHB)%.o,$@) $(ALLTESTSUPPORTINGOBJ)

$(PATHB)%.o:: $(PATHS)%.cpp $(DEP)
	echo "compiling $@ with $<"
	$(CC) -c $(CFLAGS) $< -o $@

$(PATHB)%.o:: $(PATHT)%.cpp $(DEP)
	echo "compiling $@ with $<"
	$(CC) -c $(CFLAGS) $< -o $@

$(PATHB)%.o:: $(PATHU)%.c $(DEP)
	echo "unity compiling"
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: test







	










