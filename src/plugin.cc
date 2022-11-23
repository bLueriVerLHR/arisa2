#include <cstddef>
#include <cstdio>
#include <cstring>
#include <regex>
#include <string>

#include "../ext/ctre.hpp"

#include "plugin.h"
#include "requests.h"

namespace {
bool startwith(const char *src, const char *tgt) {
  return !strncmp(src, tgt, strlen(tgt));
}
} // namespace

namespace arisa {

bool Echo::match(Json::String &input) {
  static constexpr auto pattern = ctll::fixed_string{"^/echo .+"};
  return !!ctre::match<pattern>(input);
}

bool DailyWord::match(Json::String &input) {
  static constexpr auto pattern = ctll::fixed_string{"^/dw$"};
  return !!ctre::match<pattern>(input);
}

bool arisa::bgmCalendar::match(Json::String &input) {
  static constexpr auto pattern = ctll::fixed_string{"^/bgmc$"};
  return !!ctre::match<pattern>(input);
}

bool arisa::Covid::match(Json::String &input) {
  static constexpr auto pattern = ctll::fixed_string{"^/cov$"};
  return !!ctre::match<pattern>(input);
}

bool arisa::Help::match(Json::String &input) {
  static constexpr auto pattern = ctll::fixed_string{"^/help$"};
  return !!ctre::match<pattern>(input);
}

} // namespace arisa