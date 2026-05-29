#ifndef FOUNDATION_TIME_TIMEPOINT_H
#define FOUNDATION_TIME_TIMEPOINT_H

    #include <Foundation/Time/Tick.h>
    #include <Foundation/Time/Duration.h>

    namespace Foundation {
        namespace Time {

            class Clock;

            class TimePoint {
            private:
                Tick _ticks;
                const Clock* _clock;

            public:

                constexpr TimePoint(
                    Tick ticks = 0,
                    const Clock* clock = nullptr
                )
                    : _ticks(ticks),
                    _clock(clock) {}

                constexpr Tick Ticks() const {
                    return _ticks;
                }

                const Clock* GetClock() const {
                    return _clock;
                }

                bool IsValid() const {
                    return _clock != nullptr;
                }

                Duration operator-(const TimePoint& rhs) const {
                    if (_clock != rhs._clock) {
                        return Duration(0);
                    }

                    return Duration(_ticks - rhs._ticks);
                }

                TimePoint operator+(const Duration& duration) const {
                    return TimePoint(_ticks + duration.Ticks(), _clock);
                }

                TimePoint operator-(const Duration& duration) const {
                    return TimePoint(_ticks - duration.Ticks(), _clock);
                }

                bool SameClock(const TimePoint& rhs) const {
                    return _clock == rhs._clock;
                }

                bool operator==(const TimePoint& rhs) const {
                    return (_clock == rhs._clock) &&
                        (_ticks == rhs._ticks);
                }

                bool operator!=(const TimePoint& rhs) const {
                    return !(*this == rhs);
                }
            };
        }
    }

#endif