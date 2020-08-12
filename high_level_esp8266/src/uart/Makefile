DEFS =
CFLAGS =
LDFLAGS =
INC = -I../include/uart

ESP_SDK_PATH = /home/data-scientist/esp/ESP8266_NONOS_SDK-2.2.1

ESP_SDK_INC = -I$(ESP_SDK_PATH)/include -I$(ESP_SDK_PATH)/driver_lib/include/
ESP_SDK_LIBS = -L$(ESP_SDK_PATH)/ld -L$(ESP_SDK_PATH)/lib

ESP_DEFS = -DICACHE_FLASH -DUSE_US_TIMER -D__TARGET_ESP__ $(DEFS)
ESP_CC = xtensa-lx106-elf-gcc
ESP_AR = xtensa-lx106-elf-ar
ESP_CFLAGS = -I. $(ESP_SDK_INC) -mlongcalls -Os -Wall $(ESP_DEFS) $(CFLAGS)
ESP_LIBS = \
	-lmain \
	-lnet80211 \
	-lwpa \
	-llwip \
	-lpp \
	-lphy \
	-ldriver \
	-lc \
	-lgcc \
	-lphy \
	-lpp \
	-lnet80211 \
	-lcrypto

ESP_LDFLAGS = -L. $(ESP_SDK_LIBS) -Teagle.app.v6.ld $(LDFLAGS)
ESP_LINK_FLAGS = $(ESP_LDFLAGS) \
	-nostdlib -fdata-sections -ffunction-sections \
	-Wl,-static -Wl,--gc-sections \
	-Wl,--start-group $(ESP_LIBS) -Wl,--end-group -lgcc

SRC_DIR = src
SOURCES = $(wildcard *.c)
OBJECTS_ESP = $(SOURCES:.c=.o)

LIB_PATH = ../../libs
TARGET = lib_uart.a

.PHONY: $(TARGET) clean

$(TARGET): $(OBJECTS_ESP)
	@echo link:
	$(ESP_AR) crs $(LIB_PATH)/$(TARGET) $(OBJECTS_ESP)

.c.o:
	@echo compile:
	$(ESP_CC) $(INC) $(ESP_CFLAGS) -c $< -o $@

clean:
	@echo clean uart:
	rm -f *.o
	rm -f $(LIB_PATH)/$(TARGET)