#include <thread>

#include "offsets.h"

class cPlayer {
public:
    uintptr_t LocalPlayer();
    void Jump();
    int32_t Flags();
    int32_t Health();
    int32_t CrosshairID();
    int32_t Team();
    void Shoot();
};
