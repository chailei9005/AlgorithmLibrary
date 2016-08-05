#include "Base.h"

void checkMemoryLeaks() {
#ifdef CHECK_LEAK
#ifdef _MSC_VER
    _CrtDumpMemoryLeaks();
#endif
#endif
}
