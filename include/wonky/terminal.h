#pragma once

#include <sys/termios.h>
#include <sys/ttycom.h>

namespace wonky {

class terminal {
public:

	static terminal& get();

	bool in_raw_mode() const;
	void enable_raw_mode();
	void disable_raw_mode();

	void flush();

	void update_winsize();

	// cursor movement
	void cursor_home();

	// screen operations
	void screen_clear();

private:
	explicit terminal();
	void escape(const char* value);
	void csi(const char* value);

	struct termios _termios;
	struct winsize _winsize;
	bool _in_raw_mode = false;
};

}
