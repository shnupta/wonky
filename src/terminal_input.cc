#include "terminal_input.h"

#include <unistd.h>

namespace wonky {

terminal_input::terminal_input(hula::loop<>& l)
	: _loop(l)
	, _stdin(
			_loop,
			STDIN_FILENO,
			hula::fd_slots{
				.readable = [this](int) { stdin_readable(); },
				.error = [this](int) { stdin_error(); }
			},
			hula::fd_events::read
		)
{

}

void terminal_input::stdin_readable() {
	printf("term input!\n");
	char buf[128];
	::read(STDERR_FILENO, buf, sizeof(buf));

}

void terminal_input::stdin_error() {

}

}
