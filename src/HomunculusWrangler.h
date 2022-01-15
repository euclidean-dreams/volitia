#ifndef VOLITIA_HOMUNCULUSWRANGLER_H
#define VOLITIA_HOMUNCULUSWRANGLER_H

#include "bonds/Pollable.h"
#include "Config.h"

namespace volitia {

class HomunculusWrangler : public impresarioUtils::TickingCirculable {
private:
    std::unique_ptr<std::vector<std::unique_ptr<Pollable>>> homunculusBonds;
    int tickInterval;

public:
    explicit HomunculusWrangler(std::unique_ptr<std::vector<std::unique_ptr<Pollable>>> homunculusBonds);

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;
};

}

#endif //VOLITIA_HOMUNCULUSWRANGLER_H
