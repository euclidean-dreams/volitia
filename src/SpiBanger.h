#ifndef VOLITIA_SPIBANGER_H
#define VOLITIA_SPIBANGER_H

#include <pigpio.h>
#include "Config.h"

namespace volitia {

class SpiBanger {
private:
    int spiHandle;
    int valueCount;
    int transactionSize;
    std::vector<char> values;

    void readValues();

    int determineMajorityRedundantValue(int valueIndex);

    int determineHowManyRedundantValuesAreSimilarTo(char baseValue, int valueIndex);

public:
    SpiBanger(int channel, int valueCount);

    std::unique_ptr<std::vector<char>> receive();
};

}

#endif //VOLITIA_SPIBANGER_H
