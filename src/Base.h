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
#ifdef _MSC_VER

// Redefine new operator to show specific leak info
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

// Include crt library
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif

#endif


