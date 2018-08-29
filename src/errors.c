#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "errors.h"

int lsdb_error_log(int level, int e)
{
	logmsg(level, "%s", lsdb_error_msg(e));
	return e;
}

char *lsdb_error_msg(int e)
{
	switch (e) {
		LSDB_ERROR_CODES(LSDB_ERROR_MSG)
	}
	return "Unknown error";
}

void lsdb_print_error(int e, int errsv, char *errstr)
{
	char buf[LINE_MAX];
	if (errsv != 0) {
		strerror_r(errsv, buf, sizeof(buf));
		logmsg(LOG_SEVERE, "%s: %s", errstr, buf);
	}
	else if (e != 0) {
		logmsg(LOG_SEVERE, "%s: %s", errstr, lsdb_error_msg(e));
	}
}
