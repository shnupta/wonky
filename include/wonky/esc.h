#pragma once

namespace wonky::esc {

constexpr const char* esc = "\x1b";
constexpr const char* enable_asb = "\x1b[?1049h";
constexpr const char* disable_asb = "\x1b[?1049l";
constexpr const char* erase_screen = "\x1b[2J";

}  // namespace wonky::esc
