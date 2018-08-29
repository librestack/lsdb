/* mtest.c - memory-mapped database tester/toy */
/*
 * Copyright 2011-2017 Howard Chu, Symas Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.
 *
 * A copy of this license is available in the file LICENSE in the
 * top-level directory of the distribution or, alternatively, at
 * <http://www.OpenLDAP.org/license.html>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/lsdb.h"

#define E(expr) CHECK((rc = (expr)) == MDB_SUCCESS, #expr)
#define RES(err, expr) ((rc = expr) == (err) || (CHECK(!rc, #expr), 0))
#define CHECK(test, msg) ((test) ? (void)0 : ((void)fprintf(stderr, \
	"%s:%d: %s: %s\n", __FILE__, __LINE__, msg, lsdb_strerror(rc)), abort()))

int main(int argc,char * argv[])
{
	int i = 0, j = 0, rc;
	lsdb_env *env;
	lsdb_dbi dbi;
	lsdb_val key, data;
	lsdb_txn *txn;
	lsdb_stat mst;
	lsdb_cursor *cursor, *cur2;
	lsdb_cursor_op op;
	int count;
	int *values;
	char sval[32] = "";

	srand(time(NULL));

	    count = (rand()%384) + 64;
	    values = (int *)malloc(count*sizeof(int));

	    for(i = 0;i<count;i++) {
			values[i] = rand()%1024;
	    }
    
		E(lsdb_env_create(&env));
		E(lsdb_env_set_maxreaders(env, 1));
		E(lsdb_env_set_mapsize(env, 10485760));
		E(lsdb_env_open(env, "./testdb", MDB_FIXEDMAP /*|MDB_NOSYNC*/, 0664));

		E(lsdb_txn_begin(env, NULL, 0, &txn));
		E(lsdb_dbi_open(txn, NULL, 0, &dbi));
   
		key.mv_size = sizeof(int);
		key.mv_data = sval;

		printf("Adding %d values\n", count);
	    for (i=0;i<count;i++) {	
			sprintf(sval, "%03x %d foo bar", values[i], values[i]);
			/* Set <data> in each iteration, since lsdb_NOOVERWRITE may modify it */
			data.mv_size = sizeof(sval);
			data.mv_data = sval;
			if (RES(MDB_KEYEXIST, lsdb_put(txn, dbi, &key, &data, MDB_NOOVERWRITE))) {
				j++;
				data.mv_size = sizeof(sval);
				data.mv_data = sval;
			}
	    }
		if (j) printf("%d duplicates skipped\n", j);
		E(lsdb_txn_commit(txn));
		E(lsdb_env_stat(env, &mst));

		E(lsdb_txn_begin(env, NULL, MDB_RDONLY, &txn));
		E(lsdb_cursor_open(txn, dbi, &cursor));
		while ((rc = lsdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
			printf("key: %p %.*s, data: %p %.*s\n",
				key.mv_data,  (int) key.mv_size,  (char *) key.mv_data,
				data.mv_data, (int) data.mv_size, (char *) data.mv_data);
		}
		CHECK(rc == MDB_NOTFOUND, "lsdb_cursor_get");
		lsdb_cursor_close(cursor);
		lsdb_txn_abort(txn);

		j=0;
		key.mv_data = sval;
	    for (i= count - 1; i > -1; i-= (rand()%5)) {
			j++;
			txn=NULL;
			E(lsdb_txn_begin(env, NULL, 0, &txn));
			sprintf(sval, "%03x ", values[i]);
			if (RES(MDB_NOTFOUND, lsdb_del(txn, dbi, &key, NULL))) {
				j--;
				lsdb_txn_abort(txn);
			} else {
				E(lsdb_txn_commit(txn));
			}
	    }
	    free(values);
		printf("Deleted %d values\n", j);

		E(lsdb_env_stat(env, &mst));
		E(lsdb_txn_begin(env, NULL, MDB_RDONLY, &txn));
		E(lsdb_cursor_open(txn, dbi, &cursor));
		printf("Cursor next\n");
		while ((rc = lsdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
			printf("key: %.*s, data: %.*s\n",
				(int) key.mv_size,  (char *) key.mv_data,
				(int) data.mv_size, (char *) data.mv_data);
		}
		CHECK(rc == MDB_NOTFOUND, "lsdb_cursor_get");
		printf("Cursor last\n");
		E(lsdb_cursor_get(cursor, &key, &data, MDB_LAST));
		printf("key: %.*s, data: %.*s\n",
			(int) key.mv_size,  (char *) key.mv_data,
			(int) data.mv_size, (char *) data.mv_data);
		printf("Cursor prev\n");
		while ((rc = lsdb_cursor_get(cursor, &key, &data, MDB_PREV)) == 0) {
			printf("key: %.*s, data: %.*s\n",
				(int) key.mv_size,  (char *) key.mv_data,
				(int) data.mv_size, (char *) data.mv_data);
		}
		CHECK(rc == MDB_NOTFOUND, "lsdb_cursor_get");
		printf("Cursor last/prev\n");
		E(lsdb_cursor_get(cursor, &key, &data, MDB_LAST));
			printf("key: %.*s, data: %.*s\n",
				(int) key.mv_size,  (char *) key.mv_data,
				(int) data.mv_size, (char *) data.mv_data);
		E(lsdb_cursor_get(cursor, &key, &data, MDB_PREV));
			printf("key: %.*s, data: %.*s\n",
				(int) key.mv_size,  (char *) key.mv_data,
				(int) data.mv_size, (char *) data.mv_data);

		lsdb_cursor_close(cursor);
		lsdb_txn_abort(txn);

		printf("Deleting with cursor\n");
		E(lsdb_txn_begin(env, NULL, 0, &txn));
		E(lsdb_cursor_open(txn, dbi, &cur2));
		for (i=0; i<50; i++) {
			if (RES(MDB_NOTFOUND, lsdb_cursor_get(cur2, &key, &data, MDB_NEXT)))
				break;
			printf("key: %p %.*s, data: %p %.*s\n",
				key.mv_data,  (int) key.mv_size,  (char *) key.mv_data,
				data.mv_data, (int) data.mv_size, (char *) data.mv_data);
			E(lsdb_del(txn, dbi, &key, NULL));
		}

		printf("Restarting cursor in txn\n");
		for (op=MDB_FIRST, i=0; i<=32; op=MDB_NEXT, i++) {
			if (RES(MDB_NOTFOUND, lsdb_cursor_get(cur2, &key, &data, op)))
				break;
			printf("key: %p %.*s, data: %p %.*s\n",
				key.mv_data,  (int) key.mv_size,  (char *) key.mv_data,
				data.mv_data, (int) data.mv_size, (char *) data.mv_data);
		}
		lsdb_cursor_close(cur2);
		E(lsdb_txn_commit(txn));

		printf("Restarting cursor outside txn\n");
		E(lsdb_txn_begin(env, NULL, 0, &txn));
		E(lsdb_cursor_open(txn, dbi, &cursor));
		for (op=MDB_FIRST, i=0; i<=32; op=MDB_NEXT, i++) {
			if (RES(MDB_NOTFOUND, lsdb_cursor_get(cursor, &key, &data, op)))
				break;
			printf("key: %p %.*s, data: %p %.*s\n",
				key.mv_data,  (int) key.mv_size,  (char *) key.mv_data,
				data.mv_data, (int) data.mv_size, (char *) data.mv_data);
		}
		lsdb_cursor_close(cursor);
		lsdb_txn_abort(txn);

		lsdb_dbi_close(env, dbi);
		lsdb_env_close(env);

	return 0;
}
