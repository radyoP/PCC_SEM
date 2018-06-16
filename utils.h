//
// Created by pavel on 15.6.18.
//

#ifndef PCC_SEM_UTILS_H
#define PCC_SEM_UTILS_H

#include <algorithm>

    template <typename T>
    T clamp(const T& n, const T& lower, const T& upper) {
        return std::max(lower, std::min(n, upper));
    }




#endif //PCC_SEM_UTILS_H
