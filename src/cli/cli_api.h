#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_JSON_C_H
#include <json-c/json.h>
#endif

#define CLI_HISTORY_FILE	"elfview_cli_history.txt"

struct cli_struct {
	int elf_client_fd;
};

extern struct cli_struct cli;

void cli_main(int argc, char *argv[]);
int cli_send_command(int argc, char *argv[]);

// Commands handlers
int cli_cmd_load(const struct cli_struct *cli, int argc, char *argv[]);
int cli_cmd_delete(const struct cli_struct *cli, int argc, char *argv[]);
int cli_cmd_list(const struct cli_struct *cli, int argc, char *argv[]);
int cli_cmd_select(const struct cli_struct *cli, int argc, char *argv[]);
int cli_cmd_get(const struct cli_struct *cli, int argc, char *argv[]);
int cli_cmd_test(const struct cli_struct *cli, int argc, char *argv[]);
int cli_cmd_shell(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

