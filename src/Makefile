
WTD_PROJECT = ..
include $(WTD_PROJECT)/config.local

TARGET = splice_tool.app
SRCS    = $(wildcard *.c)
OBJS    = $(SRCS:.c=.o)

LIBPNG_PATH = $(HOME)/Project/ImageProcess/libpng
ZLIB_PATH = $(HOME)/Project/ImageProcess/zlib

CFLAGS += -I${LIBPNG_PATH}/include -I${ZLIB_PATH}/include -I$(PUB_INC_DIR) -g -Wall
LDFLAGS += -L${LIBPNG_PATH}/lib -L${ZLIB_PATH}/lib
LIBS += -lpng -lz

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $^ \
		# -Wl,-gc-sections  ##OSX gcc not support -gc-sections
	mv $(TARGET) $(WTD_PROJECT)
	
%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c -fpic -Wall $< 
clean:
	rm -f $(OBJS)  $(WTD_PROJECT)/$(TARGET)

