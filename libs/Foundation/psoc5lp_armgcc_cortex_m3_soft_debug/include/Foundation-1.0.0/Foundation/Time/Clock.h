#ifndef FOUNDATION_TIME_CLOCK_H
#define FOUNDATION_TIME_CLOCK_H

    #include <Foundation/Time/Tick.h>
    #include <Foundation/Time/Frequency.h>
    #include <Foundation/Time/Period.h>
    #include <Foundation/Time/TimePoint.h>
    #include <Foundation/Utils/Callback.h>

    namespace Foundation {
        namespace Time {

            class Clock {
            public:
                using Callback = Tick (*)();

            private:
                Utils::Callback<Tick> _callback;
                Frequency _frequency;

            public:

                Clock()
                    : _frequency(0, 1) {}

                Clock( Callback callback, const Frequency& frequency )
                    : _frequency(frequency) {
                    _callback.bind(callback);
                }

                TimePoint Now() const {
                    return TimePoint(
                        _callback.status() ? _callback.invoke() : 0,
                        this
                    );
                }

                bool IsBound() const {
                    return _callback.status();
                }

                void Bind(Callback callback) {
                    _callback.bind(callback);
                }

                void Unbind() {
                    _callback.unbind();
                }

                Frequency GetFrequency() const {
                    return _frequency;
                }

                Period GetPeriod() const {
                    return _frequency.GetPeriod();
                }

                void SetFrequency(const Frequency& frequency) {
                    _frequency = frequency;
                }
            };
        }
    }

#endif