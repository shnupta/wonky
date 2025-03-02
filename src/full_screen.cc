#include "wonky/full_screen.h"

namespace wonky {

full_screen::~full_screen() {
	deinitialise();
}

void full_screen::render() {
	if (!_initialised) {
		initialise();
	}

	// todo: draw contents of buffer
}

void full_screen::initialise() {
	_term.enable_raw_mode();
	_term.screen_clear();
	_term.cursor_home();
	_term.flush();
	_initialised = true;
}

void full_screen::deinitialise() {
	if (_term.in_raw_mode()) {
		_term.disable_raw_mode();
	}
	_initialised = false;
}

}
