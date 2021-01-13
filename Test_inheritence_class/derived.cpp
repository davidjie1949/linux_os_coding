#include "derived.h"

derived::derived(int highth, double length, double width) : base {length, width}, m_highth{highth}{

}

double derived::area(){
    return 3.14 * base::length() * base::length();

}
