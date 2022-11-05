#include <cstdio>

#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>

#include "selfdef.h"
#include "requests.h"

int main() {
    initSelfDef();
    requests::initRequests();
    try {
    drogon::app()
        .setLogPath("./")
        .setLogLevel(trantor::Logger::kWarn)
        .addListener(HOST_BARE_STRING, HOST_PORT)
        .setThreadNum(16)
        // .enableRunAsDaemon()
        .run();
            } catch (std::exception &e) {
        printf("%s", e.what());
    }
    return 0;
}
