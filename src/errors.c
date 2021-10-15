#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "../include/lsdb.h"
#include "log.h"
#include "errors.h"

int lsdb_error_log(int level, int e)
{
	logmsg(level, "%s", lsdb_strerror(e));
	return e;
}

void lsdb_print_error(int e, int errsv, char *errstr)
{
	char buf[LINE_MAX];
	if (errsv != 0) {
		strerror_r(errsv, buf, sizeof(buf));
		logmsg(LOG_SEVERE, "%s: %s", errstr, buf);
	}
	else if (e != 0) {
		logmsg(LOG_SEVERE, "%s: %s", errstr, lsdb_strerror(e));
	}
}
