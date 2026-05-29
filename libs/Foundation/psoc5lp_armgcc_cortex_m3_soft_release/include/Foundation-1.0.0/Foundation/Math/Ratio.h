#ifndef FOUNDATION_MATH_RATIO_H
#define FOUNDATION_MATH_RATIO_H

    #include <stdint.h>
    #include <Foundation/Math/Arithmetic.h>

    namespace Foundation{
        namespace Math{

            class Ratio {
                private:
                    int32_t _num;
                    int32_t _den;

                    private:
                    static int32_t abs(int32_t value) {
                        return (value < 0) ? -value : value;
                    }

                public:

                    constexpr Ratio(
                        int32_t num = 0,
                        int32_t den = 1
                    )
                        : _num(num),
                        _den(den)
                    {
                    }

                    constexpr int32_t Num() const {
                        return _num;
                    }

                    constexpr int32_t Den() const {
                        return _den;
                    }

                    void SetNum(int32_t num) {
                        _num = num;
                    }

                    void SetDen(int32_t den) {
                        _den = den;
                    }

                    void Set(
                        int32_t num,
                        int32_t den
                    ) { 
                        _num = num;
                        _den = den;
                    }

                    constexpr int8_t Sign() const {
                        int a = (_num > 0) ? 1 : (_num < 0) ? -1 : 0;
                        int b = (_den > 0) ? 1 : (_den < 0) ? -1 : 0;
                        return static_cast<int8_t>(a * b);
                    }
                    constexpr bool IsValid() const {
                        return (_den != 0);
                    }

                    constexpr float ToFloat() const {
                        return IsValid()
                            ?   static_cast<float>(_num) /
                                static_cast<float>(_den)
                            : 0.0f;
                    }

                    Ratio Reduced() const {
                        if (!IsValid()) {
                            return Ratio(0, 1);
                        }

                        uint32_t gcd = Math::GCD( abs(_num), abs(_den));

                        Ratio result(
                            static_cast<int32_t>(_num / gcd),
                            static_cast<int32_t>(_den / gcd)
                        );


                        return result;
                    }

                    void Reduce() {
                        if (!IsValid()) {
                            _num = 0;
                            _den = 1;
                            return;
                        }
                        uint32_t gcd = Math::GCD(_num, _den);
                        _num /= gcd;
                        _den /= gcd;
                    }
                
            };
        }
    }

#endif