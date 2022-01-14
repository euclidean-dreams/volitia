#include "SpiBanger.h"

namespace volitia {

SpiBanger::SpiBanger(int channel, int valueCount)
        : valueCount{valueCount},
          transactionSize{valueCount * SPI_REDUNDANCY},
          values{} {
    values.resize(valueCount * SPI_REDUNDANCY, 0);
    spiHandle = spiOpen(channel, SPI_BAUDRATE, 0);
    if (spiHandle < 0) {
        LOGGER->info("failed to open spi connection, error code: {}", spiHandle);
    }
}

std::unique_ptr<std::vector<char>> SpiBanger::receive() {
    readValues();
    auto result = std::make_unique<std::vector<char>>();
    result->reserve(valueCount);
    for (int valueIndex = 0; valueIndex < valueCount; valueIndex++) {
        auto majorityValue = determineMajorityRedundantValue(valueIndex);
        if (majorityValue == -1) {
            return nullptr;
        } else {
            result->push_back(majorityValue);
        }
    }
    return result;
}

int SpiBanger::determineMajorityRedundantValue(int valueIndex) {
    auto majorityRequirement = SPI_REDUNDANCY / 2 + 1;
    for (int baseValueIndex = 0; baseValueIndex < SPI_REDUNDANCY; baseValueIndex++) {
        auto baseValue = values[baseValueIndex * valueCount + valueIndex];
        auto similarCount = determineHowManyRedundantValuesAreSimilarTo(baseValue, valueIndex);
        if (similarCount >= majorityRequirement) {
            return baseValue;
        }
    }

    // no majority found
    return -1;
}

int SpiBanger::determineHowManyRedundantValuesAreSimilarTo(char baseValue, int valueIndex) {
    int similarCount = 0;
    for (int redundantValueIndex = 0; redundantValueIndex < SPI_REDUNDANCY; redundantValueIndex++) {
        auto redundantValue = values[redundantValueIndex * valueCount + valueIndex];
        if (redundantValue == baseValue) {
            similarCount++;
        }
    }
    return similarCount;
}

void SpiBanger::readValues() {
    auto spiResult = spiRead(spiHandle, values.data(), transactionSize);
    if (spiResult != transactionSize) {
        LOGGER->info("spi write failed, error code: {}", spiResult);
    }
}

}
