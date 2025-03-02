#include "wonky/app.h"
#include "wonky/terminal.h"
#include "wonky/screen.h"

#include "terminal_input.h"

#include <hulaloop/repeater.h>

#include <memory>
#include <stdexcept>

namespace wonky {

class app::impl {
public:
	explicit impl()
		: _render_repeater(_loop, 30ms, [this] { render(); })
		, _terminput(_loop)
		, _terminal(terminal::get())
	{
		_winsize_closer = _loop.connect_to_unix_signal(hula::unix::sig::sigwinch, [&] { _terminal.update_winsize(); });
	}

	void run() {
		_render_repeater.start();
		_loop.run();
	}

	void stop() {
		_loop.stop();
	}

	hula::loop<>& runtime() {
		return _loop;
	}

	void set_screen(std::shared_ptr<screen> s) {
		_screen = s;
	}

private:

	void render() {
		_screen->render();
	}

	hula::loop<> _loop;
	hula::repeater<> _render_repeater;
	terminal_input _terminput;
	terminal& _terminal;
	std::shared_ptr<screen> _screen;

	// handles
	hula::closer _winsize_closer;
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

void app::set_screen(std::shared_ptr<screen> s) {
	_pimpl->set_screen(s);
}

}
