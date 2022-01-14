#include <pigpio.h>
#include <ImpresarioUtils.h>
#include "bonds/CalypsoBond.h"
#include "HomunculusWrangler.h"
#include "bonds/GeminiBond.h"
#include "ParcelMaster.h"

namespace volitia {

void initializePigpio() {
    auto pigpioInitializationResult = gpioInitialise();
    if (pigpioInitializationResult < 0) {
        LOGGER->info("failed to initialize pigpio - failed with error code: {}", pigpioInitializationResult);
    }
}

int bootstrap() {
    std::string configFilePath = "../config.yml";
    impresarioUtils::Bootstrapper bootstrapper(configFilePath, 1);
    initializePigpio();

    // homunculi
    auto homunculusBonds = std::make_unique<std::vector<std::unique_ptr<Pollable>>>();
    auto axiomArbiter = std::make_shared<impresarioUtils::Arbiter<std::vector<float>>>();
    homunculusBonds->push_back(std::make_unique<CalypsoBond>(axiomArbiter));

    auto phenomenaArbiter = std::make_shared<impresarioUtils::BufferArbiter<int>>();
    homunculusBonds->push_back(std::make_unique<GeminiBond>(phenomenaArbiter));

    auto homunculusWrangler = std::make_unique<HomunculusWrangler>(move(homunculusBonds));
    auto homunculusWranglerThread = impresarioUtils::Circlet::begin(move(homunculusWrangler));

    // parcel master
    auto socket = std::make_unique<impresarioUtils::NetworkSocket>(
            bootstrapper.getZmqContext(),
            ENDPOINT,
            zmq::socket_type::pub,
            true
    );
    auto parcelMaster = std::make_unique<ParcelMaster>(move(socket), move(axiomArbiter), move(phenomenaArbiter));
    auto parcelMasterThread = impresarioUtils::Circlet::begin(move(parcelMaster));

    // loop
    homunculusWranglerThread->join();
    parcelMasterThread->join();
    return 0;
}

}

int main() {
    return volitia::bootstrap();
}
