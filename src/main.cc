#include <cstdio>

#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>

#include "requests.h"
#include "selfdef.h"
#include "arisa2.h"

arisa::qqbot botarisa;

int main() {
  initSelfDef();
  requests::initRequests();
  arisa::qqloop ql{.bot = &botarisa};
  std::thread trd{ql};
  drogon::app()
      .setLogPath("./")
      .setLogLevel(trantor::Logger::kWarn)
      .addListener(HOST_BARE_STRING, HOST_PORT)
      .setThreadNum(16)
      // .enableRunAsDaemon()
      .run();
  botarisa.setend();
  trd.join();
  return 0;
}
