//////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.
// All rights reserved.

/// \file PzCameraApi.h


#ifndef _PZCAMERAAPI_h_
#define _PZCAMERAAPI_h_

#include "export.h"
#include "common/vector.h"

namespace PresenZ {
namespace Camera {
namespace PRESENZ_VERSION_NS {

/// \defgroup PzCameraApi Camera interface
/// \brief Contains the interface for the camera, so that the plugin camera can set up the origin/dir/derivates per pixel
/// \details For a specific pixel on the target image, you can request a PzCameraRay.
///
/// Depending the current phase of rendering. PzGetCameraRay() will internally invoke PzGetRayDetectPhase() / PzGetRayRenderPhase() depending of the current rendering phase.
///
/// A PzCameraRay is a small structure consisting of an origin, a direction, derivatives and finally a 
/// boolean telling if the ray is meaningful (valid) or not. If a ray is not meaningful, the ray tracer 
/// can just skip the ray and skip computation early. 
///
/// \section detection Detection Phase
///
/// The Detect phase should generate 256 samples per pixel (fixed sampling). 
///
/// \section rendering Rendering Phase
///
/// PzGetRayRenderPhase() will take x,y as an input and it can support a deviation from the pixel center (typical of 
/// filtering systems).
///
/// 
/// \section misc Misc. Phase
///
/// If needed, you can also use PzGetSpecularRay() to have a ray as if it was shot exactly at the central position 
/// of the camera. This is most likely needed when the ray tracer is generating global illumination caching 
/// data. 
/// \{
	
    ///@brief PzCameraRay defines the return value from PzGetRayDetectPhase() / PzGetRayRenderPhase() containing data (origin/dir) related to rays
    struct PzCameraRay 
    {        
        inline PzCameraRay() : valid(false),minZ(0.f) {}
		/// True if the ray should be cast, False if the ray can be discarded.
        bool valid;      
		/// ray origin
        NozPoint origin; 
		/// ray direction
        NozVector dir;   
		/// ray direction derivatives with respect to the x of target image
        NozVector dDdx;  
		/// ray direction derivatives with respect to the y of target image
        NozVector dDdy;  
		/// ray strating distance from the origin.
        float minZ;
        /// Return if the structure is valid or not.
        bool isValid() const { return valid; };
    };

    /// @brief Return a ray for a given pixel X/Y coordinate  for the current PresenZ phase. 
    /// @param[in] x Horizontal position in screen space of the pixel on the target image.
    /// @param[in] y Vertical position in screen space of the pixel on the target image.
    /// @return All the ray information contained in a PzCameraRay structure
    presenz_plugin_sdk_EXPORT PzCameraRay PzGetCameraRay(const double &x, const double &y);


    /// @brief Return a ray for a given pixel X/Y coordinate  for the current PresenZ phase. 
    /// @param[in] x Horizontal position in screen space of the pixel on the target image.
    /// @param[in] y Vertical position in screen space of the pixel on the target image.
    /// @return All the ray information contained in a PzCameraRay structure
    presenz_plugin_sdk_EXPORT PzCameraRay PzGetCameraRay(const int &pixelX, const int &pixelY);

    /// @brief Return a ray for a given pixel X/Y coordinate during the Detection Phase.
    /// The function user PzGetCurrentSampleIndexCount() internally. Use PzCameraRay.isValid() to check if the generated structure is valid.
    /// @deprecated Since 2.5.0 use PzGetCameraRay instead.
    /// @param[in] x Horizontal position in screen space of the pixel on the target image.
    /// @param[in] y Vertical position in screen space of the pixel on the target image.
    /// @return All the ray information contained in a PzCameraRay structure
    presenz_plugin_sdk_EXPORT PzCameraRay PzGetRayDetectPhase(const int &x, const int &y);


    /// @brief Return a rendering ray according to pixel X/Y coordinate in screen space.
    /// This function intenally uses PzGetCurrentSampleIndexCount() and PzGetSeed() to generate a different position inside the pixel on each call.
    /// If you are using our seeder, this function is easier to use than the others.
    /// @deprecated Since 2.5.0 use PzGetCameraRay instead.
    /// @param[in] pixelX Horizontal coordinate of the pixel on the target image.
    /// @param[in] pixelY Vertical coordinate of the pixel on the target image.
    /// @return All the ray information contained in a PzCameraRay structure
    presenz_plugin_sdk_EXPORT PzCameraRay PzGetRayRenderPhase(const int &pixelX, const int &pixelY);


    /// @brief Return the near & far clip planes for a given pixel.
    /// @param[in] pixelX Horizontal coordinate of the pixel on the target image.
    /// @param[in] pixelY Vertical coordinate of the pixel on the target image.
    /// @param[out] isVoxtrum True if the current pixel part of a voxtrum.
    /// @param[out] minz near clio plane, or -1 if invalid.
    /// @param[out] maxz far clio plane, or -1 if invalid.
    /// @return true if the ray is valid and min/max z is populated.
    presenz_plugin_sdk_EXPORT bool PzGetRayMinMaxZ(const int &pixelX, const int &pixelY, bool &isVoxtrum, float &minz, float &maxz);

    /// @brief Return a ray as if it was cast from the specularPoint of the camera. 
    /// @param[in] x Horizontal position in screen space of the pixel on the target image.
    /// @param[in] y Vertical position in screen space of the pixel on the target image.
    /// @return All the ray information contained in a PzCameraRay structure
    presenz_plugin_sdk_EXPORT  PzCameraRay PzGetSpecularRay(const double &x, const double &y);

    /// @brief Return a ray as if it was cast from the center of the camera. 
    /// @param[in] x Horizontal position in screen space of the pixel on the target image.
    /// @param[in] y Vertical position in screen space of the pixel on the target image.
    /// @return All the ray information contained in a PzCameraRay structure
    presenz_plugin_sdk_EXPORT  PzCameraRay PzGetCenterRay(const double &x, const double &y, const double &xres, double &yres);

    /// @brief Given a screen position (X,Y), this will return a random seed.
    /// @param[in] x Horizontal position in screen space of the pixel on the target image.
    /// @param[in] y Vertical position in screen space of the pixel on the target image.
    /// @return 64 bits random integer value
    presenz_plugin_sdk_EXPORT  NozUInt64 PzGetSeed(const double &x, const double &y);


    /// @brief Given a direction (X,Y,Z), this will return the u,v screen coordinates of the cubeMap projection.
    presenz_plugin_sdk_EXPORT void PzGetUVFromRay(const NozVector& dir, double& uval, double& vval);

/// \}	
}
using namespace PRESENZ_VERSION_NS;
}
}

#endif
