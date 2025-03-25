#pragma once

#include "esc.h"

#include <stdexcept>
#include <string>

#include <sys/termios.h>
#include <unistd.h>

namespace wonky {

class terminal {
 public:
  void enable_raw_mode() {
    save_buffer();

    if (tcgetattr(STDIN_FILENO, &_original_termios) != 0) {
      throw std::runtime_error("failed to get original termios settings");
    }

    struct termios raw = _original_termios;
    raw.c_lflag &= ~(ECHO | ICANON);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) != 0) {
      throw std::runtime_error("failed to set raw mode termios settings");
    }
  }

  void erase_full_screen() { write(esc::erase_screen); }

  void disable_raw_mode() {
    restore_buffer();
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &_original_termios)) {
      throw std::runtime_error("failed to restore original termios settings");
    }
  }

 private:
  void save_buffer() { write(esc::enable_asb); }

  void restore_buffer() { write(esc::disable_asb); }

  void write(const std::string& s) { write(s.data(), s.size()); }

  void write(const char* s) { write(s, std::strlen(s)); }

  void write(const char* data, size_t sz) { ::write(STDOUT_FILENO, data, sz); }

  struct termios _original_termios;
};

}  // namespace wonky
