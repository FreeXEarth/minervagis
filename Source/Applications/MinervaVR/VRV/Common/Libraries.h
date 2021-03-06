
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Author: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_COMMON_LIBRARIES_H__
#define __VRV_COMMON_LIBRARIES_H__

#include "vpr/vprParam.h"

#ifdef _MSC_VER

#if __VPR_version < 2001014

#ifdef _DEBUG

#define VPR_LIB "vpr_d-2_0.lib"
#define VRJ_LIB "vrj_d-2_2.lib"
#define CPPDOM_LIB "cppdom_d-0_7_10.lib"

#else

#define VPR_LIB "vpr-2_0.lib"
#define VRJ_LIB "vrj-2_2.lib"
#define CPPDOM_LIB "cppdom-0_7_10.lib"

#endif

#else

#ifdef _DEBUG

#define VPR_LIB "vpr-2_1_14.lib"
#define VRJ_LIB "vrj-2_3_18.lib"
#define CPPDOM_LIB "cppdom-1_0_0.lib"

#else

#define VPR_LIB "vpr-2_1_14.lib"
#define VRJ_LIB "vrj-2_3_18.lib"
#define CPPDOM_LIB "cppdom-1_0_0.lib"

#endif

// Auto-link with these libraries.
#pragma comment(lib, VPR_LIB)
#pragma comment(lib, VRJ_LIB)
#pragma comment(lib, CPPDOM_LIB)

#endif

#endif

#endif // __VRV_COMMON_LIBRARIES_H__
