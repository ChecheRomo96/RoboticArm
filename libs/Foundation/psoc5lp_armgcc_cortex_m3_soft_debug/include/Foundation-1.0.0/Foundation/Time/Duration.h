#ifndef FOUNDATION_TIME_DURATION_H
#define FOUNDATION_TIME_DURATION_H

#include <Foundation/Time/Tick.h>
#include <Foundation/Time/Period.h>

namespace Foundation {
    namespace Time {

        class Duration {
        private:
            Tick _ticks;

        public:

            constexpr Duration(Tick ticks = 0)
                : _ticks(ticks) {}

            constexpr Tick Ticks() const {
                return _ticks;
            }

            void SetTicks(Tick ticks) {
                _ticks = ticks;
            }

            bool IsZero() const {
                return _ticks == 0;
            }

            float Seconds(const Period& period) const {
                return static_cast<float>(_ticks) * period.Seconds();
            }

            float Milliseconds(const Period& period) const {
                return static_cast<float>(_ticks) * period.Milliseconds();
            }

            float Microseconds(const Period& period) const {
                return static_cast<float>(_ticks) * period.Microseconds();
            }

            Duration operator+(const Duration& rhs) const {
                return Duration(_ticks + rhs._ticks);
            }

            Duration operator-(const Duration& rhs) const {
                return Duration(_ticks - rhs._ticks);
            }

            bool operator==(const Duration& rhs) const {
                return _ticks == rhs._ticks;
            }

            bool operator!=(const Duration& rhs) const {
                return _ticks != rhs._ticks;
            }

            bool operator<(const Duration& rhs) const {
                return _ticks < rhs._ticks;
            }

            bool operator>(const Duration& rhs) const {
                return _ticks > rhs._ticks;
            }

            bool operator<=(const Duration& rhs) const {
                return _ticks <= rhs._ticks;
            }

            bool operator>=(const Duration& rhs) const {
                return _ticks >= rhs._ticks;
            }
        };
    }
}

#endif