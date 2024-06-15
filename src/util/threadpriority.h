#include <Qt>

namespace mixxx {

class ThreadPriority {
  public:
    static bool setRealtimePriority(int priority);
};

} // namespace mixxx
