#ifndef VOLITIA_PARCELMASTER_H
#define VOLITIA_PARCELMASTER_H

#include "Config.h"

namespace volitia {

class ParcelMaster : public impresarioUtils::TickingCirculable {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> socket;
    std::shared_ptr<impresarioUtils::Arbiter<std::vector<float>>> axiomArbiter;
    std::shared_ptr<impresarioUtils::BufferArbiter<int>> phenomenaArbiter;
    int tickInterval;

public:
    ParcelMaster(std::unique_ptr<impresarioUtils::NetworkSocket> socket,
                 std::shared_ptr<impresarioUtils::Arbiter<std::vector<float>>> axiomArbiter,
                 std::shared_ptr<impresarioUtils::BufferArbiter<int>> phenomenaArbiter);

    void activate() override;

    uint64_t getTickInterval() override;

    bool finished() override;
};

}

#endif //VOLITIA_PARCELMASTER_H
