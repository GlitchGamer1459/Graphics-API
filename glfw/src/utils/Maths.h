#pragma once

namespace util {

    template<typename _Tp, typename _LH>
    bool range(_Tp n, _LH low, _LH high) 
    {
        return n >= low && n <= high;
    }

}