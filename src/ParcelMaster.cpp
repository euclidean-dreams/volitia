#include "ParcelMaster.h"

namespace volitia {

ParcelMaster::ParcelMaster(std::unique_ptr<impresarioUtils::NetworkSocket> socket,
                           std::shared_ptr<impresarioUtils::Arbiter<std::vector<float>>> axiomArbiter,
                           std::shared_ptr<impresarioUtils::BufferArbiter<int>> phenomenaArbiter)
        : socket{move(socket)},
          axiomArbiter{move(axiomArbiter)},
          phenomenaArbiter{move(phenomenaArbiter)},
          tickInterval{PARCEL_MASTER_TICK_INTERVAL} {

}

void ParcelMaster::activate() {
    auto axioms = axiomArbiter->take();
    if (axioms != nullptr) {
        auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
        auto axiomsOffset = builder->CreateVector(*axioms);
        auto axiomology = ImpresarioSerialization::CreateAxiomology(*builder, axiomsOffset);
        builder->Finish(axiomology);

        socket->sendParcel(ImpresarioSerialization::Identifier::axiomology, *builder);
    }

    auto phenomena = phenomenaArbiter->take();
    for (auto &phenomenonIdentity: *phenomena) {
        auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
        auto phenomenon = ImpresarioSerialization::CreatePhenomenon(*builder, *phenomenonIdentity, 1);
        builder->Finish(phenomenon);

        socket->sendParcel(ImpresarioSerialization::Identifier::phenomenon, *builder);
    }
}

uint64_t ParcelMaster::getTickInterval() {
    return tickInterval;
}

bool ParcelMaster::finished() {
    return false;
}
}
