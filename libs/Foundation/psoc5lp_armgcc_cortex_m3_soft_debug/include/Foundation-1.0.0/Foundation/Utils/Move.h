#ifndef FOUNDATION_UTILS_MOVE_H
#define FOUNDATION_UTILS_MOVE_H

    namespace Foundation{

        /// @cond INTERNAL
        namespace Detail {

            template<typename T>
            struct RemoveReference {
                typedef T Type;
            };

            template<typename T>
            struct RemoveReference<T&> {
                typedef T Type;
            };

            template<typename T>
            struct RemoveReference<T&&> {
                typedef T Type;
            };

        }
        /// @endcond

        template <typename T>
        typename Detail::RemoveReference<T>::Type&& Move(T&& value) {
            return static_cast<typename Detail::RemoveReference<T>::Type&&>(value);
        }
    }

#endif
