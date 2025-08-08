#include "include/server.h"

int main() {
	struct foxyram *fram = init("127.0.0.1", 7000);
	run(fram);
	cleanup(fram);
	return 0;
}
