//////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.
// All rights reserved.
#ifndef _PzRenderSampleAPI_h_
#define _PzRenderSampleAPI_h_

#include "PzExport.h"
#include "common/color.h"

#include "PzPhaseApi.h"

#include <vector>
#include <array>
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

    // vec2 * float
    inline vec2 operator*(const vec2& v, float s) {
        return { v.x * s, v.y * s };
    };
    inline vec2 operator*(float s, const vec2& v) {
        return v * s;
    };

    // vec3 * float
    inline vec3 operator*(const vec3& v, float s) {
        return { v.x * s, v.y * s, v.z * s };
    };
    inline vec3 operator*(float s, const vec3& v) {
        return v * s;
    };

    // vec4 * float
    inline vec4 operator*(const vec4& v, float s) {
        return { v.x * s, v.y * s, v.z * s, v.a * s };
    };
    inline vec4 operator*(float s, const vec4& v) {
        return v * s;
    };

    inline vec2& operator*=(vec2& v, float s) {
        v.x *= s;
        v.y *= s;
        return v;
    };

    inline vec3& operator*=(vec3& v, float s) {
        v.x *= s;
        v.y *= s;
        v.z *= s;
        return v;
    };

    inline vec4& operator*=(vec4& v, float s) {
        v.x *= s;
        v.y *= s;
        v.z *= s;
        v.a *= s;
        return v;
    };

    inline vec3& operator/=(vec3& v, float s) {
        v.x /= s;
        v.y /= s;
        v.z /= s;
        return v;
    };

    inline vec4& operator/=(vec4& v, float s) {
        v.x /= s;
        v.y /= s;
        v.z /= s;
        v.a /= s;
        return v;
    };

    inline vec2 operator+(const vec2& a, const vec2& b) {
        return { a.x + b.x, a.y + b.y };
    }
    inline vec3 operator+(const vec3& a, const vec3& b) {
        return { a.x + b.x, a.y + b.y, a.z + b.z };
    }
    inline vec4 operator+(const vec4& a, const vec4& b) {
        return { a.x + b.x, a.y + b.y, a.z + b.z, a.a + b.a };
    }

    inline vec2& operator+=(vec2& a, const vec2& b) {
        a.x += b.x; a.y += b.y;
        return a;
    }
    inline vec3& operator+=(vec3& a, const vec3& b) {
        a.x += b.x; a.y += b.y; a.z += b.z;
        return a;
    }
    inline vec4& operator+=(vec4& a, const vec4& b) {
        a.x += b.x; a.y += b.y; a.z += b.z; a.a += b.a;
        return a;
    }

    ///@brief AOVData union
    union AOVData 
    {
		/// byte
        char b;
		/// integer
        int d;
		/// float
        float f;
		/// 2D vector
        vec2 v2;
		/// 3D vector
        vec3 v3;
		/// 4D vector
        vec4 v4;
        // initialize all values to zero
        AOVData() { std::memset(this, 0, sizeof(AOVData)); }
    };

    typedef struct PzRenderSamplesStorage        PzRenderSamplesStorage;
    typedef struct PzRenderSampleBuilder         PzRenderSampleBuilder;

    typedef enum PzResult {
        PZ_OK = 0,
        PZ_ERR_INVALID_ARGUMENT,
        PZ_ERR_OUT_OF_MEMORY,
        PZ_ERR_INTERNAL,
        PZ_ERR_BUFFER_TOO_SMALL,
        PZ_ERR_NOT_READY
    } PzResult;


    enum NeighborIdx {
        NEIGHBOR_TOP_LEFT = 0,
        NEIGHBOR_TOP = 1,
        NEIGHBOR_TOP_RIGHT = 2,
        NEIGHBOR_LEFT = 3,
        CENTER = 4,
        NEIGHBOR_RIGHT = 5,
        NEIGHBOR_BOTTOM_LEFT = 6,
        NEIGHBOR_BOTTOM = 7,
        NEIGHBOR_BOTTOM_RIGHT = 8
    };

    struct NeighborAgg {
        NozRGBA RGBA = { 0,0,0,0 };
        float weight = 0.0f;
    };

    ///@brief AOVData union
    union AOVDataFiltered
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
        /// 4D vector
        NeighborAgg neighborAggs[9];

        // initialize all values to zero
        AOVDataFiltered() { std::memset(this, 0, sizeof(AOVDataFiltered)); }
    };


    /** pixel data structure for filtering */
    struct PzFilteredSample
    {
        presenz_plugin_sdk_EXPORT PzFilteredSample();
        presenz_plugin_sdk_EXPORT ~PzFilteredSample();
        presenz_plugin_sdk_EXPORT PzFilteredSample(const PzFilteredSample& other);
        presenz_plugin_sdk_EXPORT PzFilteredSample(PzFilteredSample&& other) noexcept;
        presenz_plugin_sdk_EXPORT PzFilteredSample& operator=(const PzFilteredSample& other);
        presenz_plugin_sdk_EXPORT PzFilteredSample& operator=(PzFilteredSample&& other) noexcept;

        struct mainPixel {            
            double z;
            NozVector normal;
            NozVector motionVector;
            NeighborAgg neighborAggs[9];
            
            float ratio;
            int X, Y;
            uint16_t flags;
            uint8_t camNum;
            uint8_t sizeExp;

            // Constructor to zero everything
            mainPixel() {
                std::memset(this, 0, sizeof(*this));
            }

        };
        mainPixel data;

        void* unionAovsStorage;
    };

    presenz_plugin_sdk_EXPORT AOVDataFiltered*          PzGetAOVBuffer(const PzFilteredSample& s) noexcept;
    presenz_plugin_sdk_EXPORT AOVDataFiltered*          PzGetAOVAt(PzFilteredSample& s, std::size_t index) noexcept;
    
    presenz_plugin_sdk_EXPORT std::size_t               PzGetAOVCount(const PzFilteredSample& s) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzResizeAOVs(PzFilteredSample& s, std::size_t newSize) noexcept;

    presenz_plugin_sdk_EXPORT bool                      PzSetAOV(PzFilteredSample& s, size_t index, const AOVDataFiltered& data) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzSetAOV(PzFilteredSample& s, size_t index, const int& data) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzSetAOV(PzFilteredSample& s, size_t index, const bool& data) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzSetAOV(PzFilteredSample& s, size_t index, const double& data) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzSetAOV(PzFilteredSample& s, size_t index, const vec2& data) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzSetAOV(PzFilteredSample& s, size_t index, const vec3& data, const NeighborIdx& Nidx) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzSetAOV(PzFilteredSample& s, size_t index, const vec4& data, const NeighborIdx& Nidx) noexcept;

    presenz_plugin_sdk_EXPORT AOVDataFiltered           PzGetAOV(const PzFilteredSample& s, std::size_t index) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzGetAOV(const PzFilteredSample& s, size_t index, int& out) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzGetAOV(const PzFilteredSample& s, size_t index, bool& out) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzGetAOV(const PzFilteredSample& s, size_t index, double& out) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzGetAOV(const PzFilteredSample& s, size_t index, vec2& out) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzGetAOV(const PzFilteredSample& s, size_t index, const NeighborIdx& Nidx, vec3& data) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzGetAOV(const PzFilteredSample& s, size_t index, const NeighborIdx& Nidx, vec4& data) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzGetAOV(const PzFilteredSample& s, size_t index, const NeighborIdx& Nidx, NozRGBA& out, float& weight) noexcept;
    presenz_plugin_sdk_EXPORT bool                      PzAssignAOVs(PzFilteredSample& s, const AOVDataFiltered* data, std::size_t count) noexcept;



    /**
     * @brief Creates a render-sample storage container.
     *
     * The storage owns an internal list/arena of samples. The integer
     * parameters @p x and @p y capture per-storage metadata you’ll need later
     * (e.g., pixel coordinates, tile indices, or dimensions).
     *
     * @param[out] outStorage  Receives the newly created storage handle. Must not be NULL.
     * @param[in]  x           Caller-supplied integer metadata (e.g., pixel X).
     * @param[in]  y           Caller-supplied integer metadata (e.g., pixel Y).
     * @return PZ_OK on success, error otherwise.
     */
    presenz_plugin_sdk_EXPORT
        PzResult PzCreateStorage(PzRenderSamplesStorage** outStorage, int32_t x, int32_t y);

    /**
     * @brief Destroys a storage and frees all owned samples.
     *
     * @param[in] storage  Storage to destroy (NULL is allowed and is a no-op).
     * @return PZ_OK on success.
     */
    presenz_plugin_sdk_EXPORT
        PzResult PzDestroyStorage(PzRenderSamplesStorage* storage);


    /**
     * @brief Adds the current builder state as a sample into a storage.
     *
     * The builder’s contents are copied into @p storage’s internal list.
     * The builder remains valid; reuse it after @ref PzResetSampleBuilder.
     *
     * @param[in,out] storage  Target storage. Must not be NULL.
     * @param[in]     sb       Source builder. Must not be NULL.
     * @return PZ_OK on success.
     */
    presenz_plugin_sdk_EXPORT
        PzResult PzAddSampleToStorage(PzRenderSamplesStorage* storage, const PzRenderSampleBuilder* sb);

    /**
     * @brief Hints a target capacity to minimize reallocations when adding samples.
     *
     * @param[in,out] storage  Storage to reserve in.
     * @param[in]     count    Expected number of samples to add.
     * @return PZ_OK on success.
     */
    presenz_plugin_sdk_EXPORT
        PzResult PzReserveSamples(PzRenderSamplesStorage* storage, uint32_t count);

    /**
     * @brief Creates a new PresenZ sample builder instance.
     *
     * This function allocates and initializes a new @ref PzSampleBuilder object.
     * The builder is used to incrementally set individual sample attributes
     * (position, normal, color, etc.) before finalizing them into a
     * fully-defined @ref PzRenderSample structure.
     *
     * @param[out] out
     *     Pointer to a variable that will receive the address of the newly
     *     created @ref PzSampleBuilder. Must not be null.
     *
     * @return
     *     - PZ_OK on success.
     *     - PZ_ERR_INVALID_ARGUMENT if @p out is null.
     *     - PZ_ERR_OUT_OF_MEMORY if allocation fails.
     *
     * @remark
     *     The created builder must later be released with @ref PzDestroySampleBuilder
     *     to free allocated resources.
     */
    presenz_plugin_sdk_EXPORT PzResult PzCreateSampleBuilder(PzRenderSampleBuilder** out);

    /**
     * @brief Resets an existing sample builder to its default state.
     *
     * This clears all previously set field values in the given builder and
     * prepares it for constructing a new sample. The builder remains valid
     * and allocated after this call.
     *
     * @param[in,out] sb
     *     Pointer to an existing @ref PzSampleBuilder instance.
     *
     * @return
     *     - PZ_OK on success.
     *     - PZ_ERR_INVALID_ARGUMENT if @p sb is null.
     *
     * @note
     *     Any data previously set in the builder (including AOV data) is discarded.
     */
    presenz_plugin_sdk_EXPORT PzResult PzResetSampleBuilder(PzRenderSampleBuilder* sb);

    /**
     * @brief Destroys a sample builder and releases its associated resources.
     *
     * This function deallocates the memory used by the specified builder.
     * After this call, the pointer passed to @p sb becomes invalid and must
     * not be dereferenced.
     *
     * @param[in] sb
     *     Pointer to a @ref PzSampleBuilder previously created by
     *     @ref PzCreateSampleBuilder.
     *
     * @return
     *     - PZ_OK on success.
     *     - PZ_ERR_INVALID_ARGUMENT if @p sb is null.
     *
     * @warning
     *     Do not attempt to reuse the builder after destruction.
     */
    presenz_plugin_sdk_EXPORT PzResult PzDestroySampleBuilder(PzRenderSampleBuilder* sb);

    /// @brief Will tag the current sample as a glass that need to be transparent. 
    /// @param[in] sb Sample that will be updated
    /// @param[in] glass 0 for no glass, 1 for glass
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleGlass(PzRenderSampleBuilder* sb, const int& glass);

    /// @brief Will tag the current sample as a glass that need to be transparent. 
    /// @deprecated Please use PzSetSampleGlass instead.
    /// @param[in] sb Sample that will be updated
    /// @param[in] glass 0 for no glass, 1 for glass
    presenz_plugin_sdk_EXPORT PzResult PzAddGlassSampleAov(PzRenderSampleBuilder *sb, const int &glass);

    /// @brief Will tag the current sample as a mirror for RT reflections. 
    /// @param[in] sb Sample that will be updated
    /// @param[in] mirror boolean value
    presenz_plugin_sdk_EXPORT PzResult PzAddMirrorSampleAov(PzRenderSampleBuilder* sb, const bool &mirror);

    /// @brief Will tag the current sample with a specific velocity so between-frame interpolation is more accurate.  in the current sample space (see PzSetSampleSpace(Space renderSpace)).
    /// @param[in] sb Sample that will be updated
    /// @param[in] velocity 3D vector defining the speed at position which the sample move
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleVelocity(PzRenderSampleBuilder* sb, const NozVector& velocity);

    /// @brief Will tag the current sample with a specific velocity so between-frame interpolation is more accurate.  in the current sample space (see PzSetSampleSpace(Space renderSpace)).
    /// @deprecated Please use PzSetSampleVelocity instead.
    /// @param[in] sb Sample that will be updated
    /// @param[in] velocity 3D vector defining the speed at position which the sample move
    presenz_plugin_sdk_EXPORT PzResult PzAddVelocitySampleAov(PzRenderSampleBuilder* sb, const NozVector &velocity);

    /// @brief Will reference the depth of the current sample (transparency level) for filtering.
    /// @param[in] sb Sample that will be updated
    /// @param[in] depth The number of camera hits when reaching the sample's hit
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleDepth(PzRenderSampleBuilder* sb, const int &depth);

    /// @brief will tag the current sample to be in the camera space to avoid interpolation when the camera is moving    
    /// @param[in] sb Sample that will be updated
    /// @param[in] cockpit boolean defining if the current point is actually moving with the point of view
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleCockpit(PzRenderSampleBuilder* sb, const bool& cockpit);

    /// @brief will tag the current sample to be in the camera space to avoid interpolation when the camera is moving
    /// /// @deprecated Please use PzSetSampleCockpit instead.
    /// @param[in] sb Sample that will be updated
    /// @param[in] cockpit boolean defining if the current point is actually moving with the point of view
    presenz_plugin_sdk_EXPORT PzResult PzAddCockpitSampleAov(PzRenderSampleBuilder* sb, const bool &cockpit);

    /// @brief Will tag the current sample with a different color if it has been seen by the right eye. 
    /// @param[in] sb Sample that will be updated
    /// @param[in] rightColor 4D vector containing the RGB color for the right eye
    presenz_plugin_sdk_EXPORT PzResult PzAddRightColorSampleAov(PzRenderSampleBuilder* sb, const NozRGB &rightColor);

    /// @brief Add your own custom type of data.
    /// @param[in] sb Sample that will be updated
    /// @param[in] data pointer to raw data containing the AOV value for the point registered
    /// @param[in] iAlias the alias that was returned for the AOV during phase's initialization
    presenz_plugin_sdk_EXPORT PzResult PzAddSampleAov(PzRenderSampleBuilder* sb, const void* data, const int &iAlias);

    /// @brief Add your own custom type of data.
    /// @param[in] sb Sample that will be updated
    /// @param[in] data pointer to raw data containing the AOV value for the point registered
    /// @param[in] name the name that was used to register the AOV during phase's initialization
    presenz_plugin_sdk_EXPORT PzResult PzAddSampleAov(PzRenderSampleBuilder* sb, const void* data, const std::string& name);
    //////////////////////////////////////////////////////////////////////////

    /// @brief Set the sample position. Use geometric normal (raw geometry normal) instead of shaded normal (with soften / bump / normal map applied) for better result.
    /// @param[in] sb Sample that will be updated
    /// @param[in] position 3D vector representing the position of the sample in the current sample space (see PzSetSampleSpace(Space renderSpace)).
    presenz_plugin_sdk_EXPORT PzResult PzSetSamplePosition(PzRenderSampleBuilder* sb, const NozPoint &position);

    /// @brief Set the sample normal.
    /// @param[in] sb Sample that will be updated
    /// @param[in] normal 3D vector representing the normal in the current sample space (see PzSetSampleSpace(Space renderSpace)).
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleNormal(PzRenderSampleBuilder* sb, const NozVector& normal);

    /// @brief Set the X/Y inside the pixel, this will set the inPixelPosXY by keeping only the decimals
    /// @param[in] sb Sample that will be updated
    /// @param[in] xScreen X position inside the pixel
    /// @param[in] yScreen Y position inside the pixel
    presenz_plugin_sdk_EXPORT PzResult PzSetSamplePosXY(PzRenderSampleBuilder* sb, const double &xScreen, const double &yScreen);

    /// @brief Set how far from the ray origin you are
    /// @param[in] sb Sample that will be updated
    /// @param[in] z length along the ray the sample has hit something
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleZ(PzRenderSampleBuilder* sb, const double z);

    /// @brief Set the default (left eye) color for this sample
    /// @param[in] sb Sample that will be updated
    /// @param[in] rgba RGBA color for sample
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleColor(PzRenderSampleBuilder* sb, const NozRGBA &rgba);

    /// @brief Set the default (left eye) color for this sample
    /// @param[in] sb Sample that will be updated
    /// @param[in] rgba RGBA color for sample
    presenz_plugin_sdk_EXPORT PzResult PzSetSampleDirection(PzRenderSampleBuilder* sb, const NozVector& direction);

    /// @brief Forward the current RenderSample data to PresenZ bucket
    /// @param[in] bucketId The bucket the pixel is part of
    /// @param[in] pixelX Pixel position X of the sample (on the overall image)
    /// @param[in] pixelY Pixel position Y of the sample (on the overall image)
    /// @param[in] inSample sample to be saved into the bucket
    presenz_plugin_sdk_EXPORT PzResult PzProcessRenderSample(const size_t& threaId, const int& pixelX, const int& pixelY, PzRenderSampleBuilder* sb);

    typedef struct {
        const PzFilteredSample* data; ///< Pointer to the first filtered sample (read-only).
        size_t                  count; ///< Number of valid filtered samples in the span.
    } PzFilteredSpan;
    
    /// Callback function type used to receive filtered results.
    /// The callback is invoked by the filtering routine once the
    /// filtered samples are available. The `span` is only valid
    /// during the callback, so copy the data if it needs to be kept.
    typedef void (*PzFilteredCallback)(PzFilteredSpan span, void* user_data);


    /// @brief Filter render samples for a given pixel position.
    ///
    /// Processes all input render samples belonging to a single pixel.
    /// and invokes the provided callback with the filtered results.
    /// The function allocates and manages internal storage for the results,
    /// and passes them to the user through the callback.
    ///
    /// @param[in] storage The storage containing the samples to filter
    /// @param[in] cb Callback function that receives a span of filtered samples.
    /// @param[in] user_data User-provided pointer passed unchanged to the callback.
    ///
    /// @note
    /// - The span provided to the callback is only valid during the callback.
    ///   Copy the data if you need to preserve it afterwards.
    /// - The caller is responsible for managing the lifetime of the storage.
    ///   The function will read from the storage but will not free or release it.
    ///
    /// @code
    /// // Example usage
    /// void MyCallback(PzFilteredSpan span, void* user) {
    ///     std::vector<PzFilteredSample>* out = 
    ///         static_cast<std::vector<PzFilteredSample>*>(user);
    ///     out->assign(span.data, span.data + span.count);
    /// }
    ///
    /// void Example() {
    ///     // Allocate the storage and sample container (owned by the caller)
    ///     PzRenderSamplesStorage* store = NULL;
    ///     PzCreateStorage(&store, x, y); // only one per pixel
    ///     PzRenderSampleBuilder* sb = NULL; // Reuse it as much as possible, even between pixels
    ///     PzCreateSampleBuilder(&sb);
    /// 
    ///     // Fill input samples...
    ///     PzResetSampleBuilder(sb); // Reset before each new sample
    ///     PzSetSamplePosition(sb, P);
    ///     ...
    ///     PzAddSampleToStorage(store, sb);
    /// 
    ///     std::vector<PzFilteredSample> results;
    ///     PzFilterRenderSample(store, &MyCallback, &results);
    ///
    ///     // Now results contains a copy of the filtered samples
    ///
    ///     // Caller must clean up allocated storages
    ///     PzDestroySampleBuilder(sb);
    ///     PzDestroyStorage(store);
    /// }
    /// @endcode
    presenz_plugin_sdk_EXPORT void PzFilterRenderSample(
        PzRenderSamplesStorage* storage,
        PzFilteredCallback cb,
        void* user_data);


    /// @brief Get the ZDepth of a detected sampple.
    /// @param[in] pixelX Pixel position X of the sample (on the overall image)
    /// @param[in] pixelY Pixel position Y of the sample (on the overall image)
    /// @return The Z Value at the given coordinate
    presenz_plugin_sdk_EXPORT float PzGetRenderRayDepth(const int &pixelX, const int &pixelY);

    /// @brief Set the number of samples launched for a pixel. If not used, it will use an internal counter that increased on each PzGetCameraRay(const double &x, const double &y) call.
    /// @deprecated Since 4.1.0. Useless to call this function anymore.
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
