//////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.
// All rights reserved.

/// \file PzShadingApi.h

#ifndef _PZSHADINGAPI_h_
#define _PZSHADINGAPI_h_

#include "PzExport.h"
#include "PzDetectSampleApi.h"
#include "PzConstants.h"
#include "common/vector.h"
#include "PzPhaseApi.h"
#include "PzCameraApi.h"

namespace PresenZ {
namespace Shading {
namespace PRESENZ_VERSION_NS {
/// \defgroup PzShadingApi Shading interface
/// \brief Contains the shading interface for PresenZ. This interface is used in the Render Phase to process transparent rays and bend rays
/// for the left and right eye. 
/// \details 
/// \section bending Ray Bending
/// Rays are typically emitted from a camera's point of view (more specifically from it's world location). To create a stereoscopic
/// render we need to bend the rays to line up with the view of the left and right eye. 
/// \{	
	/// \brief PzBendRay is a structure representing a bend ray. 
    struct PzBendRay {
        
        inline PzBendRay() : wHitDistance(0.0), isStereoScopic(false) {}
		/// world space ray direction
        NozVector dir;  
		/// world space ray direction derivatives with respect to x
        NozVector dDdx; 
		/// world space ray direction derivatives with respect to y
        NozVector dDdy; 
        /// world space distance from the specularPoint to the hitPoint 
        double wHitDistance;
		/// can be computed for the other eye.
        bool isStereoScopic;  
    };

    /// \brief Get a ray bent from  the specular point to override the shading context.
	/// @param[in] eye The current eye we are rendering for.
    /// @param[in] GNormal The geometric normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
	/// @param[in] normal The normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
	/// @param[in] CameraDir The direction of the camera in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
	/// @param[in] hitPoint the hitpoint (shading point) in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
	/// @param[in] hitDistance Distance between the ray origin (the camera) and the current shading point.
    /// @param[in] bestCamWsPos The best camera in world position. Is acquired with PzGetBestCameraWSPosition(const int& pixelX, const int& pixelY).
	/// @return the bent ray for the respective eye.
    presenz_plugin_sdk_EXPORT PzBendRay PzGetBendRayRenderPhase(
        const PresenZ::Phase::Eye &eye, 
        const NozVector &GNormal,
        const NozVector &normal, 
        const NozVector &CameraDir, 
        const NozPoint &hitPoint, 
        const double &hitDistance,
        const NozVector & bestCamWsPos
        );

    /// \brief Get a ray bent from  the specular point to override the shading context. The bestCamWsPos parameter is computed internally.
    /// @param[in] eye The current eye we are rendering for.
    /// @param[in] GNormal The geometric normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] normal The normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] CameraDir The direction of the camera in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] hitPoint the hitpoint (shading point) in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] hitDistance Distance between the ray origin (the camera) and the current shading point.
    /// @param[in] pixelX X coordinate of the rendered pixel.
    /// @param[in] pixelY Y coordinate of the rendered pixel.
    /// @return the bent ray for the respective eye.
    presenz_plugin_sdk_EXPORT PzBendRay PzGetBendRayRenderPhase(
        const PresenZ::Phase::Eye& eye,
        const NozVector& GNormal,
        const NozVector& normal,
        const NozVector& CameraDir,
        const NozPoint& hitPoint,
        const double& hitDistance,
        const int& pixelX, 
        const int& pixelY
    );


    /// \brief Get a ray bent from  the specular point to override the shading context.
    /// @param[in] gNormal The geometric normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] normal The normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] hitPoint the hitpoint (shading point) in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] pixelX X coordinate of the pixel.
    /// @param[in] pixelY Y coordinate of the pixel.    
    /// @return the bent ray for the respective eye.
    presenz_plugin_sdk_EXPORT PzBendRay PzGetBendRayRenderPhase(
        const NozVector& gnormal,
        const NozVector& normal,
        const NozPoint& hitPoint,
        const int& pixelX,
        const int& pixelY
    );

    /// \brief Get a ray bent from  the specular point to override the shading context.
    /// @param[in] camOrigin camera origin in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] gNormal The geometric normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] normal The normal of the hitpoint in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] hitPoint the hitpoint (shading point) in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @return the bent ray for the respective eye.
    PzBendRay PzGetBendRayRenderPhase(
        const NozVector& camOrigin,
        const NozVector& gnormal,
        const NozVector& normal,
        const NozPoint& hitPoint
    );

    /// \brief Get the world position of the current scanning camera (the best camera selected for scanning this point in space).
    /// @param[in] pixelX X coordinate of the pixel.
    /// @param[in] pixelY Y coordinate of the pixel.
    /// @return the camera position in world space (see PzSetSampleSpace(Space renderSpace)).
    presenz_plugin_sdk_EXPORT NozPoint PzGetBestCameraWSPosition(const int& pixelX, const int& pixelY);

    presenz_plugin_sdk_EXPORT void getBendRayDerivative_cameraSpace(const NozPoint &worldPoint, NozVector &dDdx, NozVector &dDdy);
	/// \brief PzBendRayEx is a structure representing a transparent ray. In addition to the data a normal bend ray has, 
	/// for a transparent ray we also need to store the origin.
    struct PzBendRayEx
    {
        inline PzBendRayEx() : origin(0,0,0){};
		/// inherited PzBendRay structure
        PzBendRay pzBendRay; 
		 /// ray origin
        NozPoint origin;	
    };

    /// \brief get a ray bent from the specular point to spawn a new camera ray from the current shading context.
    presenz_plugin_sdk_EXPORT PzBendRayEx PzGetTranspRayRenderPhase(const PresenZ::Phase::Eye eye, const NozVector &normal, const NozVector &worldCameraDir, const NozPoint &worldPoint, const double &hitDistance);


    /// \brief Get the reflection direction for the current ray direction for RENDER_REFLECTION phase.
    /// @param[in] incomingDirectionWorld the incoming direction vector in current sample space coordinates. (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] x X coordinate of the pixel.
    /// @param[in] y Y coordinate of the pixel.
    /// @return the reflection ray direction
    presenz_plugin_sdk_EXPORT NozVector PzGetReflectionDirection(const NozVector incomingDirectionWorld, const double &x, const double &y);

    /// \brief Get the reflectance and transmittance value for a double sided PresenZ surface. 
    /// return false if the surface normal is not pointing to the camera. 
    presenz_plugin_sdk_EXPORT bool PzGetDoubleReflectanceTransmitance(double &outReflectance, double &outTransmitance, const double &glassTransparency, const double &glassIOR, const NozVector &incident, const NozVector &normal);

    /// \brief Query PresenZ to know if the current location should be shaded as Transparent or not.
    /// @param[in] x X coordinate of the pixel.
    /// @param[in] y Y coordinate of the pixel.
    /// @param[out] transpType return the type of transparency ( DST_opaque = 0, DST_glass = 1, DST_semiTransp = 2).
    /// @return the reflection ray direction
    presenz_plugin_sdk_EXPORT bool PzIsTransparent(const double &x, const double &y, DetectSample::DetectSample_transp &transpType);

    /// \brief During the detection phase, check if we need to sample the shader of the current sampling point for transparency informations.
    /// @param[in] hitPointWorld the position of the current sampling point in world position.
    /// @param[in] hitPointNormal  the normal of the current sampling point.
    /// @param[in] x X coordinate of the pixel.
    /// @param[in] y Y coordinate of the pixel.
    /// @param[out] goThrough true if we need to continue to trace the ray searching for the next intersection, false if we can stop here.
    /// @return True if we need to probe the current sampling point.
    presenz_plugin_sdk_EXPORT bool PzShouldProbe(const NozPoint & hitPointWorld, const NozVector & hitPointNormal, const double & x, const double & y, bool & goThrough);

    /// \brief Query PresenZ to know if the current location should be shaded as Transparent or not. 
    /// @param[in] hitPointWorld the position of the current sampling point in world position.
    /// @param[in] hitPointNormal  the normal of the current sampling point.
    /// @param[in] x X coordinate of the pixel.
    /// @param[in] y Y coordinate of the pixel.
    /// @param[out] goThrough true if we need to continue to trace the ray searching for the next intersection, false if we can stop here.
    /// @return True if we need to shade the current sampling point.
    presenz_plugin_sdk_EXPORT bool PzShouldShade(const NozPoint &hitPointWorld, const NozVector &hitPointNormal,const double &x, const double &y, bool &goThrough);

    /// \brief Query PresenZ to know if the current location should be shaded.
    /// @param[in] pixelX X coordinate of the pixel.
    /// @param[in] pixelY Y coordinate of the pixel.
    /// @param[in] hitDistance Distance between the ray origin (the camera) and the current shading point.
    /// @param[in] isChaotic Set to true if the current shaded object is tagged as "Chaotic"
    /// @param[in] isVolumetric Set to true if the current shaded object is a volumetric.
    /// @return True or false depending if the object need to be evaluated. If not, the computed sample should be RGBA(0,0,0,0).
    presenz_plugin_sdk_EXPORT bool PzIsValidEvaluation(const int &pixelX, const int &pixelY, const double &hitDistance, bool isChaotic = false, bool isVolumetric = false);

    /// \brief Get the X/Y position in [0,1[ inside the rendered pixel.
    /// @param[in] pixelX X coordinate of the pixel (rendered, like PzIsValidEvaluation).
    /// @param[in] pixelY Y coordinate of the pixel (rendered, like PzIsValidEvaluation).
    /// @param[in] pixelSampleIndex The sample index.
    /// @return a NozVector2 containing the position inside the camera pixel position.
    presenz_plugin_sdk_EXPORT NozVector2 PzGetXYInPixelPosition(const int& pixelX, const int& pixelY, const size_t &pixelSampleIndex);

    /// \brief Get the X/Y position in [0,1[ inside the rendered pixel.
/// @param[in] pixelX X coordinate of the pixel (rendered, like PzIsValidEvaluation).
/// @param[in] pixelY Y coordinate of the pixel (rendered, like PzIsValidEvaluation).
/// @param[in] incomingDir The incoming ray direction.
/// @return a NozVector2 containing the position inside the camera pixel position.
    presenz_plugin_sdk_EXPORT NozVector2 PzGetXYInPixelPosition(const int& pixelX, const int& pixelY, const NozVector& incomingDir);


    /// @brief Reset a pixel internally
    /// Note regarding thread safety: This method is not thread safe. It should be called by one thread at a time.
    /// @param[in] x Horizontal position in screen space of the pixel on the target image.
    /// @param[in] y Vertical position in screen space of the pixel on the target image.
    /// @return True if the pixel has been reset.
    presenz_plugin_sdk_EXPORT bool PzResetPixel(const int& px, const int& py);


    /// \brief Get the position in the cubemap of the current rendered pixel.
    /// @param[in] pixelX X coordinate of the pixel (rendered, like PzIsValidEvaluation).
    /// @param[in] pixelY Y coordinate of the pixel (rendered, like PzIsValidEvaluation).
    /// @param[out] outPixelX The X pixel position in the cubemap for this pixel.
    /// @param[out] outPixelY The Y pixel position in the cubemap for this pixel.
    /// @return a boolean if outPixelX/outPixelY is valid.
    presenz_plugin_sdk_EXPORT bool PzGetPixelCoordinates(const int& pixelX, const int& pixelY, int& outPixelX, int& outPixelY);

    /// \brief Query PresenZ about the current rendering resolution. (in pixels)
    /// @param[out] resX Horizontal resolution in pixels.
    /// @param[out] resY Vertical resolution in pixels.
    presenz_plugin_sdk_EXPORT void PzGetRenderingResolution(double &resX, double &resY);


    /// \brief Query PresenZ about the distance between a given point and the original scanning location.
    /// @param[in] pixelX X coordinate of the pixel.
    /// @param[in] pixelY Y coordinate of the pixel.
    /// @param[in] pos world position of the 3d coordinate.
    /// @param[out] distance the distance between a pos and the original scanning location.
    /// @return True or false depending if the distance has been be computed correctly.
    presenz_plugin_sdk_EXPORT bool PzDistanceFromCamera(const int& pixelX, const int& pixelY, const NozPoint& pos, float& distance);

/// \}
}
using namespace PRESENZ_VERSION_NS;
}
}

#endif
