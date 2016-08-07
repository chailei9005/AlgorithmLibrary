#pragma once
#ifndef BASE_H
#define BASE_H

/*
Store some configure definitions.
*/
#define NS_BEGIN namespace sl {
#define NS_END   }

/*
Memory leaks check
(available in Microsoft Visual C++ complier)
*/

//#define CHECK_LEAK

#ifdef CHECK_LEAK
#ifdef _MSC_VER

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif
#endif

/*
Check if memory leaks exist.
*/
void checkMemoryLeaks();

#endif


