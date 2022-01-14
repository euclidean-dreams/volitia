#ifndef VOLITIA_POLLABLE_H
#define VOLITIA_POLLABLE_H

#include <ImpresarioUtils.h>

namespace volitia {

class Pollable : public impresarioUtils::NonCopyable {
public:
    virtual void poll() = 0;
};

}

#endif //VOLITIA_POLLABLE_H
