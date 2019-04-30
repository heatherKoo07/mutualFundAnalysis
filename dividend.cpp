//
// Created by Heather Hyunkyung Koo on 3/10/19.
//

#include "dividend.h"

/**~*~*
    overload the insertion operator
 *~**/
std::ostream &operator << (std::ostream &strm, const Dividend &obj) {
    strm << obj.date << " " << obj.div;
    return strm;
}