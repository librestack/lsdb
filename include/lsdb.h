#ifndef _LSDB_H_
#define _LSDB_H_

#include <librecast.h>
#include <lmdb.h>

typedef struct lsdb_ctx lsdb_ctx;

typedef struct MDB_env lsdb_env;
typedef struct MDB_txn lsdb_txn;
typedef unsigned int lsdb_dbi;
typedef struct MDB_cursor lsdb_cursor;
typedef struct MDB_val lsdb_val;
typedef MDB_cursor_op lsdb_cursor_op;
typedef struct MDB_stat lsdb_stat;
typedef mdb_mode_t lsdb_mode_t;

#ifdef mdb_size_t
typedef mdb_size_t lsdb_size_t;
#else
typedef size_t lsdb_size_t;
#endif

#define LSDB_TEST 0

lsdb_ctx * lsdb_ctx_new();
void lsdb_ctx_free(lsdb_ctx *ctx);

int lsdb_env_create(lsdb_env **env);
int lsdb_env_open(lsdb_env *env, const char *path, unsigned int flags, lsdb_mode_t mode);
void lsdb_env_close(lsdb_env *env);
int lsdb_env_set_mapsize(lsdb_env *env, lsdb_size_t size);
int lsdb_env_set_maxdbs(lsdb_env *env, lsdb_dbi dbs);
int lsdb_env_set_maxreaders(lsdb_env *env, unsigned int readers);
int lsdb_env_stat(lsdb_env *env, lsdb_stat *stat);

int lsdb_txn_begin(lsdb_env *env, lsdb_txn *parent, unsigned int flags, lsdb_txn **txn);
int lsdb_txn_commit(lsdb_txn *txn);
void lsdb_txn_abort(lsdb_txn *txn);

int lsdb_dbi_open(lsdb_txn *txn, const char *name, unsigned int flags, lsdb_dbi *dbi);
void lsdb_dbi_close(lsdb_env *env, lsdb_dbi dbi);

int lsdb_get(lsdb_txn *txn, lsdb_dbi dbi, lsdb_val *key, lsdb_val *data);

int lsdb_put(lsdb_txn *txn, lsdb_dbi dbi, lsdb_val *key, lsdb_val *data, unsigned int flags);

int lsdb_del(lsdb_txn *txn, lsdb_dbi dbi, lsdb_val *key, lsdb_val *data);

int lsdb_cursor_open(lsdb_txn *txn, lsdb_dbi dbi, lsdb_cursor **cursor);
void lsdb_cursor_close(lsdb_cursor *cursor);

int lsdb_cursor_get(lsdb_cursor *cursor, lsdb_val *key, lsdb_val *data, lsdb_cursor_op op);

char *lsdb_strerror(int err);

#endif /* _LSDB_H_ */
