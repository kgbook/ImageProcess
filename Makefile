
WTD_PROJECT = ./
include $(WTD_PROJECT)/config.local

ifeq ($(version), debug)
	CFLAGS += -g -rdynamic
else ifeq ($(version), release)
	CFLAGS += -O2
else
	$(error please specify version, debug or release)
endif

all:
	make -C src all
clean:
	make -C src clean

