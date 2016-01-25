/*!***********************************************************************

 @file           PVRScopeStats.h
 @copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved.
 @brief          PVRScopeStats header file. @copybrief ScopeStats
 
**************************************************************************/

/*! @mainpage PVRScope
 
 @section overview Library Overview
*****************************
PVRScope is a utility library which has two functionalities:
 \li @ref ScopeStats is used to access the hardware performance counters in
     PowerVR hardware via a driver library called PVRScopeServices.
 \li @ref ScopeComms allows an application to send user defined information to
     PVRTune via PVRPerfServer, both as counters and marks, or as editable data that can be
     passed back to the application.

PVRScope is supplied in the PVRScope.h header file. Your application also needs to link to the PVRScope 
library file, either a <tt>.lib</tt>, <tt>.so</tt>, or <tt>.dy</tt> file, depending on your platform.
 
For more information on PVRScope, see the <em>PVRScope User Manual</em>.

 @subsection limitStats PVRScopeStats Limitations
*****************************
@copydetails ScopeStats

 @subsection limitComms PVRScopeComms Limitations
*****************************
@copydetails ScopeComms
*/

#ifndef _PVRSCOPESTATS_H_
#define _PVRSCOPESTATS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 @addtogroup ScopeStats PVRScopeStats
 @brief    The PVRScopeStats functionality of PVRScope is used to access the hardware performance counters in
           PowerVR hardware via a driver library called PVRScopeServices.
 @details  PVRScopeStats has the following limitations:
          \li Only one instance of @ref ScopeStats may communicate with PVRScopeServices at any
              given time. If a PVRScope enabled application attempts to communicate with
              PVRScopeServices at the same time as another such application, or at the same time as
              PVRPerfServer, conflicts can occur that may make performance data unreliable.
          \li Performance counters can only be read on devices whose drivers have been built with
              hardware profiling enabled. This configuration is the default in most production drivers due to negligible overhead.
          \li Performance counters contain the average value of that counter since the last time the counter was interrogated.
 @{
*/


/****************************************************************************
** Enums
****************************************************************************/

/*!**************************************************************************
 @enum          EPVRScopeInitCode
 @brief         PVRScope initialisation return codes.
****************************************************************************/
enum EPVRScopeInitCode
{
    ePVRScopeInitCodeOk,							///< Initialisation OK
    ePVRScopeInitCodeOutOfMem,						///< Out of memory
    ePVRScopeInitCodeDriverSupportNotFound,			///<