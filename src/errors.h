#ifndef __LSDB_ERRORS_H__
#define __LSDB_ERRORS_H__ 1

#include <errno.h>

/* log message and return code */
int lsdb_error_log(int level, int e);

/* print human readable error, using errsv (errno) or progam defined (e) code */
void lsdb_print_error(int e, int errsv, char *errstr);

#endif /* __LSDB_ERRORS_H__ */
