#ifndef _LSDB_H_
#define _LSDB_H_

#include <librecast.h>
#include <lmdb.h>

#define LSDB_SUCCESS MDB_SUCCESS
#define LSDB_KEYEXIST MDB_KEYEXIST
#define LSDB_NOTFOUND MDB_NOTFOUND
#define LSDB_PAGE_NOTFOUND MDB_PAGE_NOTFOUND
#define LSDB_CORRUPTED MDB_CORRUPTED
#define LSDB_PANIC MDB_PANIC
#define LSDB_VERSION_MISMATCH MDB_VERSION_MISMATCH
#define LSDB_INVALID MDB_INVALID
#define LSDB_MAP_FULL MDB_MAP_FULL
#define LSDB_DBS_FULL MDB_DBS_FULL
#define LSDB_READERS_FULL MDB_READERS_FULL
#define LSDB_TLS_FULL MDB_TLS_FULL
#define LSDB_TXN_FULL MDB_TXN_FULL
#define LSDB_CURSOR_FULL MDB_CURSOR_FULL
#define LSDB_PAGE_FULL MDB_PAGE_FULL
#define LSDB_MAP_RESIZED MDB_MAP_RESIZED
#define LSDB_INCOMPATIBLE MDB_INCOMPATIBLE
#define LSDB_BAD_RSLOT MDB_BAD_RSLOT
#define LSDB_BAD_TXN MDB_BAD_TXN
#define LSDB_BAD_VALSIZE MDB_BAD_VALSIZE
#define LSDB_BAD_DBI MDB_BAD_DBI
#define LSDB_PROBLEM MDB_PROBLEM

typedef struct lsdb_env lsdb_env;
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
int lsdb_cursor_put(lsdb_cursor *cursor, lsdb_val *key, lsdb_val *data, unsigned int flags);

char *lsdb_strerror(int err);

#endif /* _LSDB_H_ */
