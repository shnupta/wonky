#include "wonky/app.h"

#include "terminal_input.h"

#include <stdexcept>

namespace wonky {

// so how do i want this library to look?
//
// bare in mind the client application event loop will receive data and we want to pipe it into the terminal display
//
// Maybe let's split the drawing up into a screen and a then widgets.
// I think a nice abstraction is then a 'view', which is basically a bounded section of the screen.
// So views can contain a set of widgets or other views. Or is this just unnecessary?
// Widget is just the same I guess.
// We then build a tree of widgets and have them draw into the screen on a timer.
//
// screens:
// wonky::screen::full_screen()
//
// widgets:
// wonky::container_view()
//   - holds all the panes and sub children, draws top left -> bottom right
//   - automatically resizes children if they are flexible (not fixed)
// wonky::terminal_view()
//   - interprets terminal escape sequences
//
// and then each widget is given a bounded section of the screen into which it draws.
// non-visible widgets simply don't draw. 
// if widgets overlap the last drawn will be visible on top.

class app::impl {
public:
	explicit impl()
		: _termin(_loop)
	{
	}

	void run() {
		_loop.run();
	}

	void stop() {
		_loop.stop();
	}

	hula::loop<>& runtime() {
		return _loop;
	}

private:
	hula::loop<> _loop;
	terminal_input _termin;
};


// public interface

app::app()
	: _pimpl(std::make_unique<app::impl>())
{
}

app::~app() {}

void app::run() {
	_pimpl->run();
}

void app::stop() {
	_pimpl->stop();
}

hula::loop<>& app::runtime() {
	return _pimpl->runtime();
}

}
