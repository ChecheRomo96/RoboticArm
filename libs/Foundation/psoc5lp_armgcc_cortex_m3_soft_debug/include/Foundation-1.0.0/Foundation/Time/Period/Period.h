// Period.h

#ifndef FOUNDATION_TIME_PERIOD_H
#define FOUNDATION_TIME_PERIOD_H

#include <Foundation/Math/Ratio.h>

namespace Foundation {
    namespace Time {

        class Frequency;

        class Period {
        private:
            Foundation::Math::Ratio _ratio;

        public:

            Period(
                uint32_t num = 0,
                uint32_t den = 1
            );

            Period(
                const Foundation::Math::Ratio& ratio
            );

            uint32_t Num() const;

            uint32_t Den() const;

            void SetNum(uint32_t num);

            void SetDen(uint32_t den);

            void Set(
                uint32_t num,
                uint32_t den
            );

            bool IsValid() const;

            float Seconds() const;

            float Milliseconds() const;

            float Microseconds() const;

            const Foundation::Math::Ratio&
            GetRatio() const;

            Frequency GetFrequency() const;
        };

    }
}

#endif