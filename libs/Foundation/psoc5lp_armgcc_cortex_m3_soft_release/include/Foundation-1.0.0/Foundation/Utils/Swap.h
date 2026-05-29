#ifndef FOUNDATION_SWAP_H
#define FOUNDATION_SWAP_H

    #include <Foundation/Utils/Move.h>

    namespace Foundation {

        template <typename T>
        void swap(T& a, T& b) {
            T temp = Foundation::move(a);
            a = Foundation::move(b);
            b = Foundation::move(temp);
        }

    }

#endif