#pragma once

#include "screen.h"
#include "widget.h"

#include <stdexcept>

#include <hulaloop/loop.h>
#include <hulaloop/repeater.h>

namespace wonky {

constexpr auto RENDER_INTERVAL = 10ms;

class app {
 public:
  explicit app()
      : _storage_loop(new hula::loop<>()),
        _loop(_storage_loop.get()),
        _screen(_terminal),
        _render_repeater(*_loop, RENDER_INTERVAL, [this] { loop(); }) {}

  explicit app(screen::options screen_opts)
      : _storage_loop(new hula::loop<>()),
        _loop(_storage_loop.get()),
        _screen(_terminal, screen_opts),
        _render_repeater(*_loop, RENDER_INTERVAL, [this] { loop(); }) {}

  explicit app(hula::loop<>* l)
      : _loop(l),
        _screen(_terminal),
        _render_repeater(*_loop, RENDER_INTERVAL, [this] { loop(); }) {}

  explicit app(hula::loop<>* l, screen::options screen_opts)
      : _loop(l),
        _screen(_terminal, screen_opts),
        _render_repeater(*_loop, RENDER_INTERVAL, [this] { loop(); }) {}

  void run() {
    initialise();
    _render_repeater.start();
    _sigwinch_closer = _loop->connect_to_unix_signal(hula::unix::sig::sigwinch,
                                                     [this] { on_sigwinch(); });
    if (_storage_loop) {
      _storage_loop->run();
    }
  }

  void stop() {
    _render_repeater.stop();
    _sigwinch_closer.close();
    if (_storage_loop) {
      _storage_loop->stop();
    }
    deinitialise();
  }

  void set_root(widget* w) { _root = w; }

  hula::loop<>* mutable_loop() { return _loop; }

 private:
  void initialise() { _screen.initialise(); }

  void deinitialise() { _screen.deinitialise(); }

  void loop() {
    // todo: send winsize changes to the screen
    // todo: send terminal input events down the widget tree
  }

  void on_sigwinch() { printf("window size changed!\n"); }

  std::unique_ptr<hula::loop<>> _storage_loop{};
  hula::loop<>* _loop{nullptr};
  terminal _terminal{};
  screen _screen;
  hula::repeater<> _render_repeater;
  hula::closer _sigwinch_closer;

  widget* _root{nullptr};
};

}  // namespace wonky
