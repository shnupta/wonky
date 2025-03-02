#include "wonky/terminal.h"
#include "wonky/esc.h"

#include <stdexcept>
#include <iostream>
#include <unistd.h>

#include <sys/ioctl.h>

namespace wonky {

terminal& terminal::get() {
	static terminal t{};
	return t;
}

terminal::terminal() {
}

bool terminal::in_raw_mode() const {
	return _in_raw_mode;
}

void terminal::enable_raw_mode() {
	if (tcgetattr(STDIN_FILENO, &_termios))
	{
		throw std::runtime_error("tcgetattr failed trying to enable raw mode");
	}

	struct termios raw = _termios;
	// raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN); // ctrl-c will kill client in this case
	raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		throw std::runtime_error("tcsetattr failed trying to enable raw mode");
	}
	_in_raw_mode = true;
}

void terminal::disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &_termios);
	_in_raw_mode = false;
}

void terminal::flush() {
	std::cout << std::flush;
}

void terminal::escape(const char* value) {
	std::cout << esc::esc << value;
}

void terminal::csi(const char* value) {
	std::cout << esc::csi << value;
}

// cursor movement

void terminal::cursor_home() {
	csi(esc::home);
}

// screen operations

void terminal::screen_clear() {
	csi(esc::clear);
}

void terminal::update_winsize() {
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &_winsize) == -1) {
		throw std::runtime_error("failed to get winsize");
	}
	printf("winsize updated: %d %d\n", _winsize.ws_col, _winsize.ws_row);
}

}
