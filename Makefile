
WTD_PROJECT = ./
include $(WTD_PROJECT)/config.local

all:
	make -C src all
clean:
	make -C src clean

