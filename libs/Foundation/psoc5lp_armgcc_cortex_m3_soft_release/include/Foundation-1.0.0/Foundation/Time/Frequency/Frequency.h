// Frequency.h

#ifndef FOUNDATION_TIME_FREQUENCY_H
#define FOUNDATION_TIME_FREQUENCY_H

    #include <Foundation/Math/Ratio.h>

    namespace Foundation {
        namespace Time {

            class Period;

            class Frequency {
            private:
                Foundation::Math::Ratio _ratio;

            public:

                Frequency(
                    uint32_t num = 0,
                    uint32_t den = 1
                );

                constexpr Frequency(
                    const Foundation::Math::Ratio& ratio
                );

                constexpr uint32_t Num() const;

                constexpr uint32_t Den() const;

                void SetNum(uint32_t num);

                void SetDen(uint32_t den);

                void Set(
                    uint32_t num,
                    uint32_t den
                );

                bool IsValid() const;

                float Hertz() const;

                float PeriodSeconds() const;

                float PeriodMilliseconds() const;

                float PeriodMicroseconds() const;

                const Foundation::Math::Ratio&
                GetRatio() const;

                Period GetPeriod() const;
            };

            constexpr Frequency::Frequency(
                const Foundation::Math::Ratio& ratio
            )
                : _ratio(ratio) {}

            constexpr uint32_t
            Frequency::Num() const {
                return _ratio.Num();
            }

            constexpr uint32_t
            Frequency::Den() const {
                return _ratio.Den();
            }

        }
    }

#endif