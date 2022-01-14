#include "CalypsoBond.h"

namespace volitia {

CalypsoBond::CalypsoBond(std::shared_ptr<impresarioUtils::Arbiter<std::vector<float>>> axiomArbiter)
        : axiomArbiter{move(axiomArbiter)},
          spiBanger{0, 10} {

}

void CalypsoBond::poll() {
    auto rawValues = spiBanger.receive();
    if (rawValues == nullptr) {
        return;
    }
    auto homunculusValues = std::make_unique<std::vector<float>>();
    for (auto &value: *rawValues) {
        float adjustedValue = static_cast<float>(value) / 255;
        homunculusValues->push_back(adjustedValue);
    }
    axiomArbiter->give(move(homunculusValues));
}

}
