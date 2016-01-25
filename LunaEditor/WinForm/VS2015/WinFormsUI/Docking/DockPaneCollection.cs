/*!***********************************************************************

 @file           PVRScopeComms.h
 @copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved.
 @brief          PVRScopeComms header file. @copybrief ScopeComms
 
**************************************************************************/

#ifndef _PVRSCOPECOMMS_H_
#define _PVRSCOPECOMMS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
	PVRPerfServer and PVRTune communications
*/

/*!
 @addtogroup ScopeComms PVRScopeComms
 @brief      The PVRScopeComms functionality of PVRScope allows an application to send user defined information to
             PVRTune via PVRPerfServer, both as counters and marks, or as editable data that can be
             passed back to the application.
 @details    PVRScopeComms has the following limitations:
             \li PVRPerfServer must be running on the host device if a @ref ScopeComms enabled
                 application wishes to send custom cou