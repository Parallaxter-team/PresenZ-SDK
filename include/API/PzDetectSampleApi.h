//////////////////////////////////////////////////////////////////////////
// (c) Copyright 2019 - Parallaxter SPRL/Starbreeze AB 
// All rights reserved.

/// \file PzDetectSampleApi.h


#ifndef _PzDetectSampleAPI_h_
#define _PzDetectSampleAPI_h_

#include "export.h"
#include "common/vector.h"
#include "common/color.h"
#include <stdint.h>

namespace PresenZ {
namespace Camera {
namespace PRESENZ_VERSION_NS {
	
/// \defgroup PzDetectSampleApi Detection Sample interface
/// \brief Contains the interface for the PresenZ probe casting, this interface is used in the detect phase to 
/// \details calculate ray intersections with objects in the scene.These intersections also return information on the type of object that was hit. 
/// For instance, whether hair or glass was hit in the scene.
/// In the case a transparent object is hit (tagged with a "prz_transparent" tag), probe casting will ignore it and continue the detection 
/// ray until it either hits an opaque object or reaches the maximum allowed rendering distance. The interface is mostly concerned with detecting
/// which parts of the scene are visble from within the Zone Of View, we gather geometry information and forward these to PresenZ.	
/// \{
	
    ///\brief Helper function: will tell if two points can be considered the same based on their depths.
    /// @param[in] zMin The depth of the first hitpoint.
    /// @param[in] zMax The depth of the second hitpoint.
    /// @param[in] permissiveNess A factor to scale the sensitivity at which two points are considered close enough.
    /// @return True if two points are close enough to be indistinguishable, False if the points are noticeably far from eachother.
    presenz_plugin_sdk_EXPORT bool PzIsAtProximity(float zMin, float zMax, const float permissiveNess = 1.0f);
}
using namespace PRESENZ_VERSION_NS;
}
}

namespace PresenZ {
namespace DetectSample {
namespace PRESENZ_VERSION_NS {
    ///\brief RayTestResult is a simplistic structure that holds the 3D hitpoint of the ray, the normal at that point, and the total distance of the ray.
    struct RayTestResult
    {
		/// 3D hitpoint.
        NozPoint hit;		
		/// normal at the hitpoint.
        NozVector normal;	
		/// distance of ray.
        double d;	
        /// is the point Chaotic ?
        bool isChaotic;
    };

	///\brief Callback for ray test intersection.
    typedef bool(*RayTestCallback)(const NozVector& origin, const NozVector& dir, const double dist, RayTestResult& outP, void* userData);
	///\brief Callback for query of user data.
    typedef uint64_t(*QueryFlagsCallback)(uint64_t flags, void* userData);

    ///\brief This interface is forwarded to PzProcessDetectSample() so that PresenZ can perform an additional visibility check. 
    struct RayTestInterface
    {
		/// user data pointer
        void *userdata;
		/// Callback for raytracing intersection test
        RayTestCallback probe;
		/// Callback for querying render flags
        QueryFlagsCallback query;
    };


    enum DetectSample_transp {
        DST_opaque = 0,
        DST_glass = 1,
        DST_semiTransp = 2
    };
    

    //////////////////////////////////////////////////////////////////////////
    ///\brief PzDetectSample defines the structure of a detection sample. 
    struct PzDetectSample
    {
        inline PzDetectSample() : isHair(false), isChaotic(false), pixelX(0), pixelY(0), sampleIndex(0), transpType(DST_opaque) {}
		/// Is the hit object tagged as hair.
        bool isHair;
        /// Is the hit object a chaotic geometry
        bool isChaotic;
		/// Render image x coordinate.
        int pixelX;
		/// Render image y coordinate.
        int pixelY;
		/// The index of the current detect sample.
        size_t sampleIndex;
		/// Is the hit object opque/glass/semi-Transp
        DetectSample_transp transpType;
		/// Normal of the hit point in the sample coordinates (see PzSetSampleSpace(Space renderSpace)).
        NozPoint hitNormal;
		/// Hitpoint  in the sample coordinates (see PzSetSampleSpace(Space renderSpace)).
        NozPoint hitPoint; 
    };
	
	/// \brief Store the previous intersection along a camera ray
	/// this is used to avoid the detection of glass back layer 
    struct PzPreviousDetectGlassSample
    {
        inline PzPreviousDetectGlassSample(): hitPoint(0.0f), hitNormal(0.0f){}
        NozPoint hitPoint;
        NozVector hitNormal;
    };

	/// \brief During the detection phase, ray intersections need to be notified to PresenZ through PzProcessDetectSample(). This function needs to be called for each
    /// sample in the detection phase.
    /// @param[in] intfPtr A pointer to the ray test interface structure containing the information of the probe. Can be set to null for reflection detection.
    /// @param[in] sample The PzDetectSample 
    /// @param[in] threadIndex The index of the thread processing the sample
    /// @return RGBA values of the sample
    presenz_plugin_sdk_EXPORT NozRGBA PzProcessDetectSample(RayTestInterface *intfPtr, const PzDetectSample& sample, const size_t &threadIndex);
    //////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    ///\brief PzDetectSample needs to know what is the sampleIndex. In some renderers, this information can't be 
    /// reliably obtained. If this is the case, PresenZ can guess the sample index from the ray origin. 
    /// @param[in] sample The PzDetectSample 
    /// @param[in] rayOriginPos The ray origin, usually the camera position.
    presenz_plugin_sdk_EXPORT void PzMatchSampleIndex(PzDetectSample& sample, const NozPoint& rayOriginWorldPos);



    presenz_plugin_sdk_EXPORT NozPoint PzGetScanCam(int i);
/// \}	
}
using namespace PRESENZ_VERSION_NS;
}
}

#endif