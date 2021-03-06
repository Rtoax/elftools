#include <utils/log.h>
#include <utils/list.h>
#include <elf/elf_api.h>

#include "../test_api.h"

TEST(Log,	log,	0)
{
	ldebug("DEBUG\n");
	linfo("INFO\n");
	lnotice("NOTICE\n");
	lwarning("WARN\n");
	lerror("ERROR\n");
	lcrit("CRIT\n");
	lalert("ALERT\n");
	lemerg("EMERG\n");

	return 0;
}

TEST(Log,	set_log_level,	0)
{
	set_log_level(LOG_CRIT);

	ldebug("DEBUG\n");
	linfo("INFO\n");
	lnotice("NOTICE\n");
	lwarning("WARN\n");
	lerror("ERROR\n");
	lcrit("CRIT\n");
	lalert("ALERT\n");
	lemerg("EMERG\n");

	set_log_level(LOG_DEBUG);

	return 0;
}
