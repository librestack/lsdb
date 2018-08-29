#include "test.h"
#include "../include/lsdb.h"

int main()
{
	//test_assert("verify sizeof", sizeof(MDB_env) == sizeof(lsdb_ctx_db_t));

	test_summary();

	return 0;
}
