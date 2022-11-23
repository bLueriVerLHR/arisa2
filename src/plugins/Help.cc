#include "../../ext/ctre.hpp"
#include "../plugin.h"

Json::String arisa::Help::act(const std::shared_ptr<Json::Value> &json) {
  return "/echo <msg>  复读"
         "\n"
         "/cov   查看辽宁疫情"
         "\n"
         "/dw    名人名言"
         "\n"
         "/bgmc  今日番剧";
}