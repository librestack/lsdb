#define _GNU_SOURCE
#include "../include/lsdb.h"
#include "errors.h"
#include "log.h"
#include <stdlib.h>

typedef struct lsdb_env {
	MDB_env *env;
} lsdb_env;

int lsdb_env_create(lsdb_env **env)
{
	*env = calloc(1, sizeof(lsdb_env));
	if (!env) return -ENOMEM;
	return mdb_env_create(&(*env)->env);
}

int lsdb_env_open(lsdb_env *env, const char *path, unsigned int flags, lsdb_mode_t mode)
{
	return mdb_env_open(env->env, path, flags, mode);
}

void lsdb_env_close(lsdb_env *env)
{
	mdb_env_close(env->env);
	free(env);
}

int lsdb_env_set_mapsize(lsdb_env *env, lsdb_size_t size)
{
	return mdb_env_set_mapsize(env->env, size);
}

int lsdb_env_set_maxdbs(lsdb_env *env, lsdb_dbi dbs)
{
	return mdb_env_set_maxdbs(env->env, dbs);
}

int lsdb_env_set_maxreaders(lsdb_env *env, unsigned int readers)
{
	return mdb_env_set_maxreaders(env->env, readers);
}

int lsdb_env_stat(lsdb_env *env, lsdb_stat *stat)
{
	return mdb_env_stat(env->env, stat);
}

int lsdb_txn_begin(lsdb_env *env, lsdb_txn *parent, unsigned int flags, lsdb_txn **txn)
{
	return mdb_txn_begin(env->env, parent, flags, txn);
}

int lsdb_txn_commit(lsdb_txn *txn)
{
	return mdb_txn_commit(txn);
}

void lsdb_txn_abort(lsdb_txn *txn)
{
	mdb_txn_abort(txn);
}

int lsdb_dbi_open(lsdb_txn *txn, const char *name, unsigned int flags, lsdb_dbi *dbi)
{
	return mdb_dbi_open(txn, name, flags, dbi);
}

void lsdb_dbi_close(lsdb_env *env, lsdb_dbi dbi)
{
	mdb_dbi_close(env->env, dbi);
}

int lsdb_get(lsdb_txn *txn, lsdb_dbi dbi, lsdb_val *key, lsdb_val *data)
{
	return mdb_get(txn, dbi, key, data);
}

int lsdb_put(lsdb_txn *txn, lsdb_dbi dbi, lsdb_val *key, lsdb_val *data, unsigned int flags)
{
	return mdb_put(txn, dbi, key, data, flags);
}

int lsdb_del(lsdb_txn *txn, lsdb_dbi dbi, lsdb_val *key, lsdb_val *data)
{
	return mdb_del(txn, dbi, key, data);
}

int lsdb_cursor_open(lsdb_txn *txn, lsdb_dbi dbi, lsdb_cursor **cursor)
{
	return mdb_cursor_open(txn, dbi, cursor);
}

void lsdb_cursor_close(lsdb_cursor *cursor)
{
	mdb_cursor_close(cursor);
}

int lsdb_cursor_get(lsdb_cursor *cursor, lsdb_val *key, lsdb_val *data, lsdb_cursor_op op)
{
	return mdb_cursor_get(cursor, key, data, op);
}

int lsdb_cursor_put(lsdb_cursor *cursor, lsdb_val *key, lsdb_val *data, unsigned int flags)
{
	return mdb_cursor_put(cursor, key, data, flags);
}

char *lsdb_strerror(int err)
{
	return mdb_strerror(err);
}
