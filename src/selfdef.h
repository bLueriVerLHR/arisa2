#pragma once

#include <cstdio>
#include <string>

constexpr char HOST_ADDR[4] = {127, 0, 0, 1};
constexpr short HOST_PORT = 5710;

constexpr char BOT_ADDR[4] = {127, 0, 0, 1};
constexpr short BOT_PORT = 5700;

void initSelfDef();

extern char HOST_STRING[30];
extern char HOST_BARE_STRING[30];
extern char BOT_STRING[30];