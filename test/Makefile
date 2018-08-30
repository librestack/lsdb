TESTS = local mtest mtest2

test: all
	rm -rf testdb && mkdir testdb
	@for T in $(TESTS); do ./$$T; done

mtest: mtest.c
	$(CC) $(CFLAGS) mtest.c -o mtest -llmdb -llsdb

mtest2: mtest2.c
	$(CC) $(CFLAGS) mtest2.c -o mtest2 -llmdb -llsdb

all: $(TESTS)

.PHONY: clean

clean:
	rm -rf testdb
	-$(RM) $(TESTS)
