DEFS =
CFLAGS =
LDFLAGS =
INC = -Iinc

ESP_SDK_PATH = /home/data-scientist/esp/ESP8266_NONOS_SDK-2.2.1

ESP_SDK_INC = -I$(ESP_SDK_PATH)/include
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
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS_ESP = $(SOURCES:.c=.o)

TARGET = esp-image

.PHONY: $(TARGET) \
		clean \
		erase_flash \
		flash_esp_init_data_default \
		flash_user_program

$(TARGET): esp-elf
	@echo elf2image:
	esptool.py elf2image $^ -o $@

esp-elf: $(OBJECTS_ESP)
	@echo link:
	$(ESP_CC) $(INC) $(ESP_CFLAGS) -o $@ $(OBJECTS_ESP) $(ESP_LINK_FLAGS)

.c.o:
	@echo compile:
	$(ESP_CC) $(INC) $(ESP_CFLAGS) -c $< -o $@

clean:
	@echo clean:
	rm -f $(SRC_DIR)/*.o
	rm -f *.a
	rm -f *.bin
	rm -f esp-elf

erase_flash:
	@echo erase flash:
	esptool.py --port /dev/ttyUSB0 -b 115200  erase_flash

flash_esp_init_data_default:
	@echo flash esp_init_data_default
	esptool.py --port /dev/ttyUSB0 write_flash 0xFC000 $(ESP_SDK_PATH)/bin/esp_init_data_default_v05.bin

flash_user_program:
	@echo flash:
	esptool.py --port /dev/ttyUSB0 -b 115200  write_flash --no-compress 0x00000 $(TARGET)0x00000.bin 0x10000 $(TARGET)0x10000.bin