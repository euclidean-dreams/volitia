#include "HomunculusWrangler.h"

namespace volitia {

HomunculusWrangler::HomunculusWrangler(std::unique_ptr<std::vector<std::unique_ptr<Pollable>>> homunculusBonds)
        : homunculusBonds{move(homunculusBonds)},
          tickInterval{HOMUNCULUS_WRANGLER_TICK_INTERVAL} {

}

void HomunculusWrangler::activate() {
    for (auto &homunculusBond: *homunculusBonds) {
        homunculusBond->poll();
    }
}

uint64_t HomunculusWrangler::getTickInterval() {
    return tickInterval;
}

bool HomunculusWrangler::finished() {
    return false;
}

}
