#include "selfdef.h"

char HOST_STRING[30] = {0};
char BOT_STRING[30] = {0};
char HOST_BARE_STRING[30] = {0};

void initSelfDef() {
  sprintf(HOST_BARE_STRING, "%d.%d.%d.%d", HOST_ADDR[0], HOST_ADDR[1],
          HOST_ADDR[2], HOST_ADDR[3]);
  sprintf(HOST_STRING, "%d.%d.%d.%d:%d", HOST_ADDR[0], HOST_ADDR[1],
          HOST_ADDR[2], HOST_ADDR[3], HOST_PORT);
  sprintf(BOT_STRING, "%d.%d.%d.%d:%d", BOT_ADDR[0], BOT_ADDR[1], BOT_ADDR[2],
          BOT_ADDR[3], BOT_PORT);
}
