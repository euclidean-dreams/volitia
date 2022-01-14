#ifndef VOLITIA_CONFIG_H
#define VOLITIA_CONFIG_H

#include <ImpresarioUtils.h>

// endpoint
#define ENDPOINT impresarioUtils::Config::getInstance().getString("endpoint")

// spi
#define SPI_REDUNDANCY impresarioUtils::Config::getInstance().getInt("spi_redundancy")
#define SPI_BAUDRATE impresarioUtils::Config::getInstance().getInt("spi_baudrate")

// tick interval
#define PARCEL_MASTER_TICK_INTERVAL impresarioUtils::Config::getInstance().getInt("parcel_master_tick_interval")
#define HOMUNCULUS_WRANGLER_TICK_INTERVAL impresarioUtils::Config::getInstance().getInt("homunculus_wrangler_tick_interval")

#endif //VOLITIA_CONFIG_H
