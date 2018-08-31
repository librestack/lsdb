PREFIX = /usr/local
export PREFIX

LIB_PATH = $(PREFIX)/lib
export LIB_PATH

INCLUDE_PATH = $(PREFIX)/include
export INCLUDE_PATH

CFLAGS += -Wall -Werror
export CFLAGS

LIBNAME = lsdb
export LIBNAME

all:
	@$(MAKE) -C src $@

.PHONY: install clean test mtest

install:
	@$(MAKE) -C src $@

clean:
	@$(MAKE) -C src $@
	@$(MAKE) -C test $@

test:
	@$(MAKE) -C test $@

mtests:
	@$(MAKE) -C test $@
