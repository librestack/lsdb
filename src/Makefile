CFLAGS += -fPIC
LIBNAME ?= lsdb
LIBFILE = lib$(LIBNAME).so
LIBS = -llmdb
OBJECTS = $(LIBNAME).o errors.o log.o misc.o

all: $(LIBFILE)

$(LIBFILE): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $(LIBFILE) $(OBJECTS) $(LIBS)

$(LIBNAME).o: ../include/$(LIBNAME).h $(LIBNAME).c
	$(CC) $(CFLAGS) -c $(LIBNAME).c $(LIBS)

errors.o: errors.h errors.c
	$(CC) $(CFLAGS) -c errors.c $(LIBS)

log.o: log.h log.c
	$(CC) $(CFLAGS) -c log.c $(LIBS)

misc.o: misc.h misc.c
	$(CC) $(CFLAGS) -c misc.c $(LIBS)

install: $(LIBFILE)
	cp $(LIBFILE) $(LIB_PATH)/$(LIBFILE).1.0
	ln -sf $(LIB_PATH)/$(LIBFILE).1.0 $(LIB_PATH)/$(LIBFILE).1
	ln -sf $(LIB_PATH)/$(LIBFILE).1 $(LIB_PATH)/$(LIBFILE)
	install -d $(INCLUDE_PATH)
	install ../include/* $(INCLUDE_PATH)
	ldconfig

.PHONY: clean

clean:
	$(RM) *.o $(LIBFILE)
