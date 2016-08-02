#include "Base.h"

void checkMemoryLeaks() {
#ifdef _MSC_VER
    _CrtDumpMemoryLeaks();
#endif
}
