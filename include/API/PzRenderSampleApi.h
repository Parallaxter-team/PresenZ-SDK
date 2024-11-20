//////////////////////////////////////////////////////////////////////////
// (c) Copyright 2019 - Parallaxter SPRL/Starbreeze AB 
// All rights reserved.
#ifndef _PzRenderSampleAPI_h_
#define _PzRenderSampleAPI_h_

#include "export.h"
#include "common/color.h"

#include "PzPhaseApi.h"

#include <vector>
#include <cstring>

/// \file PzRenderSampleApi.h

namespace PresenZ {
namespace RenderSample {
namespace PRESENZ_VERSION_NS {

/// \defgroup RenderSample Render Sample interface
/// \brief Description of structure and API related to samples generated during the rendering phase.
///  \details
/// \section sample Sample format
///
/// Every time the renderer shades a sample, it should create an analog RenderSampleData that will receive 
/// the data used for shading.
///
/// The bulk of a PzRenderSample consists of: the position, the normal, the depth, the main color and 
/// the X and Y position inside the pixel. All the fields should be set by calling the following methods:
///     - PzSetSamplePosition()
///     - PzSetSampleNormal()
///     - PzSetSamplePosXY()
///     - PzSetSampleZ()
///     - PzSetSampleColor()
///
/// On top of that, you can attach arbitrary data per sample, typically
/// called AOV (Array Of Value) because they are stored as 2D image (arrays) next to the actual image. 
/// 
/// \section AOV AOV format
/// 
/// The actual format of AOVs is defined during the render initialization phase (see PzContextApi.h). You 
/// can fill the AOVData with the corresponding type and invoke PzAddSampleAov().
///
/// There are predefined AOVs for data that can help PresenZ interpret your data and output better images: 
///
///  - Glass (boolean): This sample comes from a geometry that is voluntarily transparent. 
///  - Velocity (3D vector): will help for high framerate movement interpolation needed for some VR headset.
///  - Cockpit (boolean): notify if translation is camera dependent (needed for motion blur)
///  - Right Eye Color (3D vector): can set up another channel for the second eye (mostly used in reflections).
///
/// These AOV have predefined methods that must be called with correct typed arguments.
///
/// \section reference Referring the sample to PresenZ
/// 
/// Once every component of your sample have been set up, you can forward the data to PresenZ using 
/// PzProcessRenderSample and you must specify to what bucket the sample belongs to and what is the 2D X,Y integer
/// position within the image.
/// \{
    //////////////////////////////////////////////////////////////////////////

    ///@brief Plain old data for 2D vectors (x, y) without constructor so it can be used in an union
	/// 
    struct vec2 { 
	    /// x value
        float x;
	    /// y value
	    float y; 
    };

    ///@brief Plain old data for 3D vectors (x, y, z) without constructor so it can be used in an union
    struct vec3 { 
	    /// x value
        float x;
	    /// y value
        float y;
	    /// z value
	    float z; 
	};

    ///@brief Plain old data for 4D vectors (x, y, z, a) without constructor so it can be used in an union
    struct vec4 {
	    /// x value
        float x;
        /// y value
        float y;
        /// z value
        float z;
	    /// a value
	    float a;
	};

    struct przAOV {
        float r;
        float g;
        float b;
        uint32_t cockpit : 1; 
        uint32_t transp : 2;   // 0 : opaque ; 1 : transpGlass ; 2 : stencil//not implemented
        uint32_t depth : 5;    // up to 31 depths 
        uint32_t voxtrum : 1;  // not set at sample level but at pixel level ( after clustering )  
    };

    ///@brief AOVData union
    union AOVData 
    {
		/// byte
        char b;
		/// integer
        int d;
		/// double
        double f;
		/// 2D vector
        vec2 v2;
		/// 3D vector
        vec3 v3;
		/// 4D vector
        vec4 v4;
        /// PresenZ Internals
        przAOV prz;

        // initialize all values to zero
        AOVData() { std::memset(this, 0, sizeof(AOVData)); }
    };

    struct PzRenderSample;

    ///@brief Will tag the current sample as a glass that need to be transparent. 
    /// @param[in] sample Sample that need to be initialized.
    presenz_plugin_sdk_EXPORT void PzInitSampleAov(PzRenderSample &sample);


    ///@brief Data containing all relevant information regarding a shading phase sample
    struct PzRenderSample
    {
        inline PzRenderSample() : pos(0.f, 0.f, 0.f), normal(0.f, 0.f, 0.f), RGBA(0.f, 0.f, 0.f, 0.f), z(0.0), inPixelPosXY(nozPoint2(0., 0.))
        {
            PzInitSampleAov(*this);
        }
		/// 3D Position
        NozPoint pos;
		/// Normal
        NozPoint normal;
		/// Color
        NozRGBA RGBA;
		/// pixel values
        NozVector2 inPixelPosXY;
		/// depth (Z)
        double z;
        /// Extra values per sample
        std::vector<AOVData> AOVs;
    };

    /** pixel data structure for filtering */
    struct PzFilteredSample
    {
        PzFilteredSample() {}

        struct mainPixel {
            double z;
            NozVector normal;
            NozRGBA RGBA;
            int X, Y;
            int32_t camNum;
            int sizeExp;
            bool isFlipped;
        };

        mainPixel data;
        std::vector<AOVData> unionAovs;
    };

    
    /// @brief Will tag the current sample as a glass that need to be transparent. 
    /// @param[in] sample Sample that will be updated
    /// @param[in] glass 0 for no glass, 1 for glass
    presenz_plugin_sdk_EXPORT void PzAddGlassSampleAov(PzRenderSample &sample, const int &glass);

    /// @brief Will tag the current sample as a mirror for RT reflections. 
    /// @param[in] sample Sample that will be updated
    /// @param[in] mirror boolean value
    presenz_plugin_sdk_EXPORT void PzAddMirrorSampleAov(PzRenderSample &sample, const bool &mirror);

    /// @brief Will tag the current sample with a specific velocity so between-frame interpolation is more accurate. 
    /// @brief deprecated ! use PzAddVelocitySampleAov instead
    /// @param[in] sample Sample that will be updated
    /// @param[in] velocity 3D vector defining the speed at position which the sample move
    presenz_plugin_sdk_EXPORT void PzAddWSVelocitySampleAov(PzRenderSample &sample, const NozVector &velocity);
    
    /// @brief Will tag the current sample with a specific velocity so between-frame interpolation is more accurate.  in the current sample space (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] sample Sample that will be updated
    /// @param[in] velocity 3D vector defining the speed at position which the sample move
    presenz_plugin_sdk_EXPORT void PzAddVelocitySampleAov(PzRenderSample &sample, const NozVector &velocity);

    /// @brief Will reference the depth of the current sample (transparency level) for filtering.
    /// @param[in] sample Sample that will be updated
    /// @param[in] cockpit Integer defining the transparency level.
    presenz_plugin_sdk_EXPORT void PzSetSampleDepth(PzRenderSample &sample, const int &depth);

    /// @brief will tag the current sample to be in the camera space to avoid interpolation when the camera is moving
    /// @param[in] sample Sample that will be updated
    /// @param[in] cockpit boolean defining if the current point is actually moving with the point of view
    presenz_plugin_sdk_EXPORT void PzAddCockpitSampleAov(PzRenderSample &sample, const bool &cockpit);

    /// @brief Will tag the current sample with a different color if it has been seen by the right eye. 
    /// @param[in] sample Sample that will be updated
    /// @param[in] rightColor 4D vector containing the RGB color for the right eye
    presenz_plugin_sdk_EXPORT void PzAddRightColorSampleAov(PzRenderSample &sample, const NozRGB &rightColor);

    /// @brief Add your own custom type of data.
    /// @param[in] sample Sample that will be updated
    /// @param[in] data pointer to raw data containing the AOV value for the point registered
    /// @param[in] iAlias the alias that was returned for the AOV during phase's initialization
    presenz_plugin_sdk_EXPORT void PzAddSampleAov(PzRenderSample &sample, const void* data, const int &iAlias);

    /// @brief Add your own custom type of data.
    /// @param[in] sample Sample that will be updated
    /// @param[in] data pointer to raw data containing the AOV value for the point registered
    /// @param[in] name the name that was used to register the AOV during phase's initialization
    presenz_plugin_sdk_EXPORT void PzAddSampleAov(PzRenderSample& sample, const void* data, const std::string& name);
    //////////////////////////////////////////////////////////////////////////

    /// @brief Set the sample position. Use geometric normal (raw geometry normal) instead of shaded normal (with soften / bump / normal map applied) for better result.
    /// @param[in] sample Sample that will be updated
    /// @param[in] position 3D vector representing the position of the sample in the current sample space (see PzSetSampleSpace(Space renderSpace)).
    presenz_plugin_sdk_EXPORT void PzSetSamplePosition(PzRenderSample &sample, const NozPoint &position);

    /// @brief Set the sample normal.
    /// @param[in] sample Sample that will be updated
    /// @param[in] normal 3D vector representing the normal in the current sample space (see PzSetSampleSpace(Space renderSpace)).
    presenz_plugin_sdk_EXPORT void PzSetSampleNormal(PzRenderSample &sample, const NozVector& normal);

    /// @brief Set the X/Y inside the pixel, this will set the inPixelPosXY by keeping only the decimals
    /// @param[in] sample Sample that will be updated
    /// @param[in] xScreen X position inside the pixel
    /// @param[in] yScreen Y position inside the pixel
    presenz_plugin_sdk_EXPORT void PzSetSamplePosXY(PzRenderSample &sample, const double &xScreen, const double &yScreen);

    /// @brief Set how far from the ray origin you are
    /// @param[in] sample Sample that will be updated
    /// @param[in] z length along the ray the sample has hit something
    presenz_plugin_sdk_EXPORT void PzSetSampleZ(PzRenderSample &sample, const double z);

    /// @brief Set the default (left eye) color for this sample
    /// @param[in] sample Sample that will be updated
    /// @param[in] rgba RGBA color for sample
    presenz_plugin_sdk_EXPORT void PzSetSampleColor(PzRenderSample &sample, const NozRGBA &rgba);

    /// @brief Forward the current RenderSample data to PresenZ bucket
    /// @param[in] bucketId The bucket the pixel is part of
    /// @param[in] pixelX Pixel position X of the sample (on the overall image)
    /// @param[in] pixelY Pixel position Y of the sample (on the overall image)
    /// @param[in] depth Number of transparent hits when reaching the sample's hit
    /// @param[in] inSample sample to be saved into the bucket
    presenz_plugin_sdk_EXPORT void PzProcessRenderSample(const size_t& bucketId, const int& pixelX, const int& pixelY, PzRenderSample& inSample);

    /// @brief Filter the current RenderSample data
    /// @param[in] x Pixel position X of the sample (on the overall image)
    /// @param[in] y Pixel position X of the sample (on the overall image)
    /// @param[in] renderSamples Array of renderSamples to filter
    /// @param[in] pixelXY_Results the filtered samples array.
    presenz_plugin_sdk_EXPORT void PzFilterRenderSample(const size_t& x, const size_t& y, std::vector<PzRenderSample>& renderSamples, std::vector<PzFilteredSample>& pixelXY_Results);


    /// @brief Get the ZDepth of a detected sampple.
    /// @param[in] pixelX Pixel position X of the sample (on the overall image)
    /// @param[in] pixelY Pixel position Y of the sample (on the overall image)
    /// @return The Z Value at the given coordinate
    presenz_plugin_sdk_EXPORT float PzGetRenderRayDepth(const int &pixelX, const int &pixelY);

    /// @brief Set the number of samples launched for a pixel. If not used, it will use an internal counter that increased on each PzGetCameraRay(const double &x, const double &y) call.
    /// @param[in] pixelX Pixel position X of the sample (on the overall image)
    /// @param[in] pixelY Pixel position Y of the sample (on the overall image)
    /// @param[in] count The number of samples launch by the camera for the specified pixel.
    presenz_plugin_sdk_EXPORT void PzSetSamplesCount(const int& pixelX, const int& pixelY, const int &count);

    //////////////////////////////////////////////////////////////////////////

/// \}
	
} // End namespace PRESENZ_VERSION_NS
using namespace PRESENZ_VERSION_NS;
} 
} 

#endif //_sampleAPI_h_
