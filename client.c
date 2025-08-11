#include "include/client.h"
#include "include/shell.h"
#include <signal.h>
#include <unistd.h>

int main() {
	signal(SIGPIPE, SIG_IGN);
	struct ridaore_cli *fram = init("127.0.0.1", 7000);
	struct ridaore_shell *shell;
	cli_connect(fram);
	shell = shell_init(fram);
	run(shell);
	
	close(fram->fd);
	return 0;
}
