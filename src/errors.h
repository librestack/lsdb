#ifndef __LSDB_ERRORS_H__
#define __LSDB_ERRORS_H__ 1

#include <errno.h>

#define LSDB_ERROR_CODES(X) \
	X(0, LSDB_ERROR_SUCCESS,             "Success") \
	X(1, LSDB_ERROR_FAILURE,             "Failure") \
	X(2, LSDB_ERROR_CONFIG_NOTNUMERIC,   "Numeric config value not numeric") \
	X(3, LSDB_ERROR_CONFIG_BOUNDS,       "Numeric config value out of bounds") \
	X(4, LSDB_ERROR_CONFIG_BOOLEAN,      "Invalid boolean config value") \
	X(5, LSDB_ERROR_CONFIG_READFAIL,     "Unable to read config file") \
	X(6, LSDB_ERROR_CONFIG_INVALID,      "Error in config file") \
	X(7, LSDB_ERROR_MALLOC,              "Memory allocation error") \
	X(8, LSDB_ERROR_CTX_REQUIRED,        "Context required for this operation") \
	X(9, LSDB_ERROR_DB_OPEN,             "Unable to open database") \
	X(10, LSDB_ERROR_DB_EXEC,            "Error executing database operation") \
	X(11, LSDB_ERROR_DB_REQUIRED,        "Database required") \
	X(12, LSDB_ERROR_DB_KEYNOTFOUND,     "Requested key not found in database") \
	X(13, LSDB_ERROR_INVALID_PARAMS,     "Invalid arguments to function")
#undef X

#define LSDB_ERROR_MSG(code, name, msg) case code: return msg;
#define LSDB_ERROR_ENUM(code, name, msg) name = code,
enum {
	LSDB_ERROR_CODES(LSDB_ERROR_ENUM)
};

/* log message and return code */
int lsdb_error_log(int level, int e);

/* return human readable error message for e */
char *lsdb_error_msg(int e);

/* print human readable error, using errsv (errno) or progam defined (e) code */
void lsdb_print_error(int e, int errsv, char *errstr);

#endif /* __LSDB_ERRORS_H__ */
