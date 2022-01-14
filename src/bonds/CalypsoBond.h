#ifndef VOLITIA_CALYPSOBOND_H
#define VOLITIA_CALYPSOBOND_H

#include "bonds/Pollable.h"
#include "SpiBanger.h"

namespace volitia {

class CalypsoBond : public Pollable {
private:
    std::shared_ptr<impresarioUtils::Arbiter<std::vector<float>>> axiomArbiter;
    SpiBanger spiBanger;

public:
    explicit CalypsoBond(std::shared_ptr<impresarioUtils::Arbiter<std::vector<float>>> axiomArbiter);

    void poll() override;
};

}

#endif //VOLITIA_CALYPSOBOND_H
