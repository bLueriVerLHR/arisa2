#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <regex>
#include <string>

#include "../../ext/ctre.hpp"
#include "../plugin.h"
#include "../requests.h"

constexpr char calendar[] = "https://api.bgm.tv/calendar";

static char present[4] = {0};

static Json::Value cache;

static char weeks[7 + 1][4]{"???", "Mon", "Tus", "Wed",
                            "Thu", "Fri", "Sat", "Sun"};

static bool checkcache() {
  char week[4];
  FILE *res = popen("date", "r");
  fscanf(res, "%s ", week);
  std::cout << week;
  return !strncmp(present, week, 3);
}

static int update() {
  char week[4];
  FILE *res = popen("date", "r");
  fscanf(res, "%s ", week);
  strncpy(present, week, sizeof(present) / sizeof(*present));
  for (int i = 1; i < 8; ++i) {
    if (!strncmp(weeks[i], week, 3)) {
      return i;
    }
  }
  return 0;
}

Json::String arisa::bgmCalendar::act(const std::shared_ptr<Json::Value> &json) {
  static int wk = 0;
  if (!checkcache()) {
    wk = update();
    cache = requests::get(calendar);
  }
  auto &&this_week = cache[wk - 1];
  auto &&items = this_week["items"];
  const auto &&len = items.size();
  std::stringstream oss;
  for (int i = 0; i < len; ++i) {
    auto &&cur = items[i];
    oss << i << ". " << cur["name_cn"].asString() << "("
        << cur["name"].asString() << ")" << std::endl;
  }
  return oss.str();
}
