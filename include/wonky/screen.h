#pragma once

#include "cell.h"
#include "sizing.h"
#include "terminal.h"

#include <vector>

namespace wonky {

class back_buffer {
 public:
  explicit back_buffer() = default;

  explicit back_buffer(size s) { resize(s); }

  void resize(size s) {
    _size = s;
    _cells.resize(s.height, std::vector<cell>(s.width));
  }

  cell& mutable_cell(coord c) { return _cells.at(c.y).at(c.x); }

  const cell& get_cell(coord c) const { return _cells.at(c.y).at(c.x); }

  void clear() {
    _cells.clear();
    resize(_size);
  }

 private:
  size _size{};
  std::vector<std::vector<cell>> _cells{};
};

class screen {
 public:
  enum class display_mode {
    inplace,  // todo
    full_screen
  };

  struct options {
    display_mode display{display_mode::full_screen};
  };

  explicit screen(terminal& term) : _terminal(term) {}
  explicit screen(terminal& term, options opts)
      : _terminal(term), _options(opts) {}

  void initialise() {
    _terminal.enable_raw_mode();

    switch (_options.display) {
      case display_mode::full_screen:
        _terminal.erase_full_screen();
        break;
      default:
        break;
    }
  }

  void deinitialise() { _terminal.disable_raw_mode(); }

 private:
  terminal& _terminal;
  options _options{};
  back_buffer _buf;
};

}  // namespace wonky
