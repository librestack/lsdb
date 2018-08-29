TESTS = local mtest

test: all
	@for T in $(TESTS); do ./$$T; done

mtest: mtest.c
	$(CC) $(CFLAGS) mtest.c -o mtest -llmdb -llsdb

all: $(TESTS)

.PHONY: clean

clean:
	-$(RM) $(TESTS)
