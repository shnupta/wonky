#pragma once

#include <hulaloop/loop.h>
#include <hulaloop/scoped_fd.h>

namespace wonky {

class terminal_input {
public:
	explicit terminal_input(hula::loop<>& l);

private:
	void stdin_readable();
	void stdin_error();

	hula::loop<>& _loop;
	hula::scoped_fd _stdin;
};

}
