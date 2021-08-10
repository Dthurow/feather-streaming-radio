DIR := ${CURDIR}
SKETCH = $(DIR)/src/internet_streaming.ino
BUILD_DIR = $(DIR)/build
BOARD = huzzah
LIBS = $(DIR)/inc $(HOME)/.arduino15/packages/esp8266/hardware/esp8266/2.7.4/libraries $(HOME)/Arduino/libraries 
include $(HOME)/makeEspArduino/makeEspArduino.mk