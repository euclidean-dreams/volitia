#include "GeminiBond.h"

namespace volitia {

GeminiBond::GeminiBond(std::shared_ptr<impresarioUtils::BufferArbiter<int>> phenomenaArbiter)
        : phenomenaArbiter{move(phenomenaArbiter)},
          spiBanger{1, 10} {

}

void GeminiBond::poll() {
    auto rawValues = spiBanger.receive();
    if (rawValues == nullptr) {
        return;
    }
    for (int index = 0; index < rawValues->size(); index++) {
        if ((*rawValues)[index] > 0) {
            phenomenaArbiter->give(std::make_unique<int>(index));
        }
    }
}

}
