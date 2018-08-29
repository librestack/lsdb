TESTS = local mtest

test: all
	rm -rf testdb && mkdir testdb
	@for T in $(TESTS); do ./$$T; done

mtest: mtest.c
	$(CC) $(CFLAGS) mtest.c -o mtest -llmdb -llsdb

all: $(TESTS)

.PHONY: clean

clean:
	rm -rf testdb
	-$(RM) $(TESTS)
