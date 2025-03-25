#pragma once

#include <cstdint>
#include <string>
#include <type_traits>

namespace wonky {

class colour {
 public:
  explicit colour() : colour(0) {}

  explicit colour(uint8_t ansi) : _type(type::ansi), ansi_code(ansi) {}

  explicit colour(uint8_t r, uint8_t g, uint8_t b)
      : _type(type::true_colour), rgb({r, g, b}) {}

 private:
  enum class type { ansi, true_colour };

  type _type{type::ansi};
  union {
    uint8_t ansi_code;
    struct {
      uint8_t r, g, b;
    } rgb;
  };
};

template <class Enum>
class flags {
 public:
  using underlying_type = std::underlying_type_t<Enum>;

  constexpr flags() = default;

  constexpr void set(Enum v) { _value |= static_cast<underlying_type>(v); }

  constexpr void unset(Enum v) { _value &= ~static_cast<underlying_type>(v); }

  constexpr bool test(Enum v) {
    return _value & static_cast<underlying_type>(v);
  }

  constexpr void clear() { _value = {}; }

 private:
  underlying_type _value{};
};

enum class attributes {
  none = 0,
  bold = 1 << 0,
  underline = 1 << 1,
};

using cell_attrs = flags<attributes>;

class cell {
 public:
  explicit cell() = default;

  void set_fg(colour fg) { _fg = fg; }

  void set_bg(colour bg) { _bg = bg; }

  void set_attr(attributes a) { _attrs.set(a); }

  void unset_attr(attributes a) { _attrs.unset(a); }

  void clear_attrs() { _attrs.clear(); }

 private:
  std::string _glyph{};
  colour _fg{};
  colour _bg{};
  cell_attrs _attrs{};
};

}  // namespace wonky
