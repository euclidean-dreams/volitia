#ifndef VOLITIA_GEMINIBOND_H
#define VOLITIA_GEMINIBOND_H

#include "bonds/Pollable.h"
#include "SpiBanger.h"

namespace volitia {

class GeminiBond : public Pollable {
private:
    std::shared_ptr<impresarioUtils::BufferArbiter<int>> phenomenaArbiter;
    SpiBanger spiBanger;

public:
    explicit GeminiBond(std::shared_ptr<impresarioUtils::BufferArbiter<int>> phenomenaArbiter);

    void poll() override;
};

}

#endif //VOLITIA_GEMINIBOND_H
