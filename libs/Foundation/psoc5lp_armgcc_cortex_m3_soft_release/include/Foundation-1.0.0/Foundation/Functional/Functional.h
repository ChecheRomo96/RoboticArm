#ifndef FOUNDATION_FUNCTIONAL_MODULE_H
#define FOUNDATION_FUNCTIONAL_MODULE_H

    #include <Foundation_BuildSettings.h>

    #if __has_include(<Foundation/Functional/Callback.h>)
        #ifndef FOUNDATION_FUNCTIONAL_CALLBACK
            #define FOUNDATION_FUNCTIONAL_CALLBACK
        #endif
        #include <Foundation/Functional/Callback.h>
    #endif

#endif//FOUNDATION_FUNCTIONAL_MODULE_H
