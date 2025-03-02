#pragma once

#include "screen.h"

#include <hulaloop/loop.h>

#include <memory>

namespace wonky {

// todo: allow intercepting terminal input

class app {
public:
	explicit app();
	~app();

	void run();
	void stop();
	void set_screen(std::shared_ptr<screen>);
	// in case the user wants to hook into the event loop
	// todo: replace this, likely we want to pass the runtime in rather than grab this one
	hula::loop<>& runtime();

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

}
