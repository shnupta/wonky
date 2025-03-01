#pragma once

#include <hulaloop/loop.h>

#include <memory>

namespace wonky {

class app {
public:
	explicit app();
	~app();

	void run();
	void stop();
	// in case the user wants to hook into the event loop
	hula::loop<>& runtime();

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

}
