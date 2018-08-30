TESTS = local mtest mtest2 mtest3 mtest4 mtest5

test: all
	rm -rf testdb && mkdir testdb
	@for T in $(TESTS); do ./$$T; done

mtest: mtest.c
	$(CC) $(CFLAGS) mtest.c -o mtest -llmdb -llsdb

mtest2: mtest2.c
	$(CC) $(CFLAGS) mtest2.c -o mtest2 -llmdb -llsdb

mtest3: mtest3.c
	$(CC) $(CFLAGS) mtest3.c -o mtest3 -llmdb -llsdb

mtest4: mtest4.c
	$(CC) $(CFLAGS) mtest4.c -o mtest4 -llmdb -llsdb

mtest5: mtest5.c
	$(CC) $(CFLAGS) mtest5.c -o mtest5 -llmdb -llsdb

all: $(TESTS)

.PHONY: clean

clean:
	rm -rf testdb
	-$(RM) $(TESTS)
