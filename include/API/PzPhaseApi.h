//////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.
// All rights reserved.

/// \file PzPhaseApi.h

#ifndef _PZPHASE_h_
#define _PZPHASE_h_

#include "export.h"
#include "PzConstants.h"
#include "common/matrix.h"
#include "common/PzDefine.h"

namespace PresenZ {
    namespace Phase {
        namespace PRESENZ_VERSION_NS {
            /// \defgroup PzPhaseApi Phase interface
            /// \brief Contains the interface for the PresenZ context, which defines how PresenZ is initialized
            /// \\details The PresenZ Context keeps track of information needed by PresenZ to do a render.
            /// A few examples of the type of data stored in the context are the transparency rendering type, whether the 
            /// left or right eye is being rendered, and what phase we are in.
            ///
            /// Initializing the PresenZ context is always started with PzInitPhase(), followed by setting the several options
            /// using all the PzSetXXXParameters(...) functions. Once this is done, the render is ready to begin. Starting the 
            /// actual phase is done by invoking PzPhaseBegin(). Lastly, after executing the phase, PzPhaseTerminate should be 
            /// invoked to release resources.
            ///
            /// \section init PzInitPhase()
            /// The first call to PresenZ that will initialize a Detection phase or a Render phase. 
            /// Additionally, this function informs PresenZ which render engine is being used.
            ///
            /// \section setters PzSetters
            /// Before executing the phase, the parameters with which to run it should be set using the multiple functions provided.
            ///
            /// \section begin PzPhaseBegin()
            /// Effectively executes the phase (= detection or render).
            ///
            /// \section terminate PzPhaseTerminate()
            /// The last call to be made after processing all the buckets. PzPhaseTerminate() will write the buckets to disk. 
            /// It will throw errors if PzInitPhase() and PzPhaseBegin() were not called beforehand.
            /// \{
            presenz_plugin_sdk_EXPORT bool PzIsMyPlaque(const int& x, const int& y, const size_t& pcam, const size_t& pX, const size_t& pY);

            /// @brief This is the very first call to PresenZ. This will tell PresenZ what you are about to render.
            /// @param[in] phase The current phase to render.
            /// @param[in] renderEngineId The id of the current render engine in use.
            presenz_plugin_sdk_EXPORT void PzInitPhase(const Phase& phase, const PresenZ::Util::RenderingEngineId& renderEngineId);

            /// @brief Set the current camera transform. This is a camera matrix. You do not have to call both, calling only one of them is sufficient.
            /// @param[in] camToWorld A 4x4 matrix  defining the camera to world transformation.
            presenz_plugin_sdk_EXPORT void PzSetCameraToWorldMatrix(const NozMatrix& camToWorld);
            /// @param[in] worldToCam A 4x4 matrix  defining the world to camera transformation.
            presenz_plugin_sdk_EXPORT void PzSetWorldToCamMatrix(const NozMatrix& worldToCam);

            /// @brief Set the resolution that you want for the final PresenZ image (this value must be equal for each Phase).
            /// @param[in] resX The width of the render image.
            /// @param[in] resY the height of the render image.
            presenz_plugin_sdk_EXPORT void PzSetOutputResolution(const size_t& resX, const size_t& resY);

            /// @brief Set the box scaling (in units) of the Zone of View.
            /// @param[in] scaleX The width of the box.
            /// @param[in] scaleY The height of the box.
            /// @param[in] scaleZ The depth of the box/
            presenz_plugin_sdk_EXPORT void PzSetZovScaling(const float& scaleX, const float& scaleY, const float& scaleZ);

            /// @brief Allow renders inside the render box (false by default, only outside (landscape mode) is renderer). 
            /// Turn on if there are objects are located within the Zone of View.
            /// @param[in] renderInside Boolean to turn on or off inside rendering.
            presenz_plugin_sdk_EXPORT void PzSetRenderInsideBox(bool renderInside);

            /// @brief By default, PresenZ will return coordinates in camera space for when launching rays from the camera. 
            /// @param[in] renderSpace Define the space that will be used to return vectors & points when launching rays from the camera.
            presenz_plugin_sdk_EXPORT void PzSetCameraSpace(Space renderSpace);

            /// @brief By default, PresenZ will take & return coordinates in world space for when launching rays for detectSamples & renderSamples. 
            /// @param[in] renderSpace Define the space that will be used to return vectors & points when launching rays for detect & render samples.
            presenz_plugin_sdk_EXPORT void PzSetSampleSpace(Space renderSpace);

            /// @brief Will affect how PresenZ computes ray derivatives, to be set at PresenZ::Phase initialization
            /// By default, PresenZ will compute UNSCALED derivatives
            /// @param[in] ray derivatives type
            presenz_plugin_sdk_EXPORT void PzSetRayDerivativeType(enum RayDerivativeType);

            /// @brief By default for froxtrum rendering, the PresenZ::Camera will move the camera ray origin in the scene to perform shading
            /// PresenZ is anyway modifying the camera origin, but while froxtrum rendering it is doing this far more. 
            /// /!\ In vray, moving the camera origin affects the way the lightCache is queried to limit this effect it's possible to use nearClip along the ray instead of moving the ray origin  
            /// @param[in] cameraRayOrigin defines if PresenZ::PzGetRayRenderPhase() will return a ray with the origin modified or with different starting distance
            presenz_plugin_sdk_EXPORT void PzSetFroxtrumRayOrigin(FroxtrumRayOrigin  froxtrumRayOrigin);

            /// @brief By default, froxtrum rendering is off. This allow to turn that feature on.
            /// @param[in] enabled Set the state of the froxtrum feature
            presenz_plugin_sdk_EXPORT void PzSetFroxtrum(const bool& enabled = false);

            /// @brief Set the depth density of frustrum. By default, it's set to 6. Lower will increase froxtrum density, higher will lower it. Another good value is 7.
            /// @param[in] depth Set the depth of the froxtrums
            presenz_plugin_sdk_EXPORT void PzSetFroxtrumDepth(const int& depth = 6);

            /// @brief Set the depth density of volumetrics. By default, it's set to 9. Lower will increase volumetrics density, higher will lower it.
            /// @param[in] depth Set the depth of the volumetrics
            presenz_plugin_sdk_EXPORT void PzSetVolumeDepth(const int& depth = 9);

            /// @brief Set the resolution of frustrum. By default, it's set to 8x8 square.
            /// @param[in] resolution resolution of the foxtrum
            presenz_plugin_sdk_EXPORT void PzSetFroxtrumResolution(const int& resolution = 8);

            /// @brief Set the offset (in units) of the center of the Zone of View.
            /// @param[in] offsetX The x coordinate in 3D space where the ZOV should be located.
            /// @param[in] offsetY The y coordinate in 3D space where the ZOV should be located.
            /// @param[in] offsetZ The z coordinate in 3D space where the ZOV should be located.
            presenz_plugin_sdk_EXPORT void PzSetZovOffset(const int& offsetX, const int& offsetY, const int& offsetZ);

            /// @brief Set the output file where you want the data (and intermediary data) to be saved.
            /// @param[in] fullPathFile A string containing the complete path (with file extension) where the write the output data to.
            presenz_plugin_sdk_EXPORT void PzSetOutFilePath(const char* fullPathFile);

            /// @brief Set the file path to the Detection File created during the first phase. This is typically used for the Render Phase.
            /// @param[in] fullPathFile A string containing the complete path (with file extension) to the Detection File.
            presenz_plugin_sdk_EXPORT void PzSetDetectFilePath(const char* fullPathFile);

            /// @brief Set the final scale of the 3D points, scaling by 0.1 will make everything 10 times closer
            /// @param[in] renderScale The scale at which the scene will be rendered.
            presenz_plugin_sdk_EXPORT void PzSetRenderScale(const double& renderScale = 1.0);

            /// @brief Set the scene Up Vector 
            /// @deprecated since 2.3.0 use PzSetCameraUpVector instead.
            /// @param[in] up The 3D vector describing the up direction in the scene.
            presenz_plugin_sdk_EXPORT void PzSetSceneUpVector(const NozVector& up);

            /// @brief Set the camera Up Vector 
            /// All rotation removed on the camera, in which axis(in scene space), the up vector of the camera is pointing to ?
            /// @param[in] up The 3D vector describing the camera up direction in the scene.
            presenz_plugin_sdk_EXPORT void PzSetCameraUpVector(const NozVector& up);


            /// @brief Set Deep reflection data. Eye will be which is currently looking at geometry. If both eyes are 
            /// used, IPD will define the inter pupillary distance, distance between the eyes (in units, mm by default).
            /// @param[in] eye The current rendering eye
            /// @param[in] IPD the distance between the two eyes in mm
            presenz_plugin_sdk_EXPORT void PzSetDeepReflection(const Eye& eye, const double& IPD = 63.5);

            /// @brief Set motion vector computation. You should enable this if you want to record geometry velocities for better animation frame interpolation. 
            /// If the ray tracer supports it, it should register velocities as a stream of "AOV" under the name
            /// of "velocity". It is only needed for animations, so it can be forcefully turned off.
            /// @param[in] detectMotionVector Boolean enabling or disabling motion vector computation.
            presenz_plugin_sdk_EXPORT void PzSetMotionVector(const bool& detectMotionVector);

            /// @brief Set what is the estimated distance from ground. 1.6 in meters by default. 
            /// @param[in] distanceToGround The height from the ground in meters.
            presenz_plugin_sdk_EXPORT void PzSetDistanceToGround(const double& distanceToGround = 1.6);

            /// @brief Set what is the maximum distance where points should be considered as geometry. Points
            /// further than this distance will be considered as being part of an infinite background sphere. 
            /// @param[in] infinity The maximum distance within which we will consider points as geometry.
            presenz_plugin_sdk_EXPORT void PzSetMaxDistance(const double& infinity);

            /// @brief Set a ratio where quality can deteriorate per points (between 0-1, ideally: 0.25) so that they can be . This is only used during
            /// the first pass to assign points to correct cameras.
            /// @param[in] infinity 
            presenz_plugin_sdk_EXPORT void PzSetTolerance(const double& infinity);

            /// @brief Set the number of thread that will perform the rendering. Each thread will be able to 
            /// register their samples autonomously. 
            /// @param[in] bucketNumber the Number of threads that will work on buckets.
            presenz_plugin_sdk_EXPORT void PzSetThreadNumber(const size_t& bucketNumber);

            /// @brief Declare if we are using an external ray counter, using PzSetSamplesCount
            /// @param[in] hasExternalCounter true if we are using a external counter.
            presenz_plugin_sdk_EXPORT void PzSetExternalCounter(const bool& hasExternalCounter = false);

            /// @brief Declare if we are using wants to the legacy sample merger.
            /// @param[in] useLegacy true if we are using the legacy code.
            presenz_plugin_sdk_EXPORT void PzSetLegacySampleMerger(const bool& useLegacy = false);

            /// @brief Set the width and height for each render bucket.
            /// @param[in] width The width of the bucket.
            /// @param[in] height The height of the bucket.
            presenz_plugin_sdk_EXPORT void PzSetBucketSize(const size_t& width, const size_t& height);

            /// @brief set filter to the Detection phase at rendering-time (as opposed to postRender filtering time) .
            /// @param[in] filter. 
            presenz_plugin_sdk_EXPORT void PzSetDetectionRTFilters(const DetectionRTFiltering& filter = no_filter);

            /// @brief Set which transparency pass you are about to render. Use PRZ_REGULAR if you are not 
            /// handling transparent points yet. 
            /// @param[in] type The type of glass rendering used.
            /// @param[in] glassThickness render the back layer of the glass if the glass thickness (in cm) is greater than glassThickness 
            presenz_plugin_sdk_EXPORT void PzSetRenderTransparencyMode(const TransparencyRenderingType& type = PRZ_REGULAR, float glassThickness = 1.0f);

            /// @brief Set which will be the POV used for computing specularity during the rendering phase. 
            /// @param[in] specularPointOffset The 3D coordinates from which specularity will be computed.
            presenz_plugin_sdk_EXPORT void PzSetSpecularPointOffset(const NozVector& specularPointOffset);

            /// @brief Set to true if you want to shortcut the rendering and have a quick preview. 
            /// @param[in] isDraft A boolean turning draft rendering on/off.
            presenz_plugin_sdk_EXPORT void PzSetDraft(const bool& isDraft = true);

            /// @brief Set which frame you are about to render. this is only relevant for animations, set 
            /// the frameNumber to 0 otherwise. 
            /// @param[in] frameNumber The number of the frame being rendered.
            /// @param[in] padding TODO this parameter needs to be removed as it is no longer used.
            presenz_plugin_sdk_EXPORT void PzSetCurrentFrame(const int& frameNumber, const size_t& padding = 4);

            /// @brief Set the clipping sphere (optional). The clipping sphere allows you to only render a part of your scene. 
            /// Anything inside/outside the sphere will be clipped.
            /// @param[in] enabled Enables or disables the clipping sphere.
            /// @param[in] worldPos The 3D world coordinates at which the sphere will be located([0,0,0] by default).
            /// @param[in] radius The radius of the sphere (100 by default).
            /// @param[in] clipInside A Boolean that determines whether to render everything inside the clipping sphere or outside.
            presenz_plugin_sdk_EXPORT void PzSetClippingSphere(bool enabled, const NozVector& worldPos = NozVector(0.0f), const float radius = 100.0f, const bool clipInside = false);

            /// @brief lower the PresenZ definition by x2, x6 or x24 to prevent having points below a predefined size  
            /// @param[in] size, in (cm)
            presenz_plugin_sdk_EXPORT void PzSetIdealPointSizeTarget(const double& idealPointsize);

            /// @brief Detection saveguard. trigger a safeguard action when the number of detect block is above blockNumber
            presenz_plugin_sdk_EXPORT void PzSetDetectionSaveguard(const float& blockNumber = 8.0, unsigned char DSG_ORedFlags = DSG_error);

            /// @brief Render from a shape with custom camera positions,normals an priority, instead of a box zone of view
            /// @param[in] windowShapesFilePath : path to a przWindowShapes file which can hold multiple shapes
            /// @param[in] windowShapeIndex: render with the shape at specified index in the windowShapeFile
            presenz_plugin_sdk_EXPORT void PzSetWindowShapesFile(const char* windowShapesFilePath, int windowShapeIndex);

            /// @brief enforce PresenZ to perform the detection from a distance (in cm ) bigger than the input parameter. 
            /// This prevents from having too much definition where the scene geometries are close from the window shape.
            /// If not set the PZ SDK will use the default 1.5cm
            /// @param[in] minimumDistance : in cm. Cannot be below 1.5 cm
            presenz_plugin_sdk_EXPORT void PzSetDetectionMinimumDistance(double minimumDistance);
            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////

            /// @brief Function to register an AOV to presenZ. You can register an arbitrary number of AOV per pixel. 
            presenz_plugin_sdk_EXPORT void PzRenderPhaseRegisterAov(const int& iAlias, const char* name, const AOVType& type);


            /// @brief Function to get the number of AOV registered to presenZ. 
            presenz_plugin_sdk_EXPORT size_t PzRenderPhaseGetNumAov();

            presenz_plugin_sdk_EXPORT void PzGetAOVInfo(const int32_t& index, std::string& name, AOVType& type);

            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////

            /// @brief Blocking mode support. During the render phase, it is very possible that you have to render more 
            /// pixels than the current render target resolution allows. If this is the case, PresenZ can render in multiple "blocks"
            /// You will invoke the render target multiple times and invoke PzSetCurrentBlockIndex(x) accordingly.
            struct PzResolutionParam {
                inline PzResolutionParam() : valid(false), resolutionX(0), resolutionY(0), blockCount(0) {};
                size_t resolutionX; /**< resolutionX current render target resolution in X (width) */
                size_t resolutionY; /**< current render target resolution in Y (height) */
                size_t blockCount; /**< total numbers of blocks */
                bool valid; /**< validity */
            };

            /// @brief Get the resolution to set the rendering engine and to process the phase in one block.
            /// @return The PZResolutionParam containing the information of the block.
            presenz_plugin_sdk_EXPORT const PzResolutionParam PzGetRenderingResolutionParameters();

            /// @brief Get the resolution to set the rendering engine and to process the phase with a custom number of blocks
            /// This lets you split the process in multiple parts which can be rendered individually. 
            /// @param[in] blockNumber The number of the current block to be rendered.
            /// @return The PZResolutionParam containing the information of requested the block.
            presenz_plugin_sdk_EXPORT const PzResolutionParam PzComputeRenderingResolutionParameters(const size_t& blockNumber);

            /// @brief Get the number of blocks needed to render the phase with a custom resolution.
            /// In this case, the renderingParams in output will hold the same resolution as the resX and resY
            /// @param[in] resX The width of render image.
            /// @param[in] resY The height of render image.
            /// @return The PZResolutionParam containing the rendering resolution parameters for the specified render image size.
            presenz_plugin_sdk_EXPORT const PzResolutionParam PzComputeRenderingResolutionParameters(const size_t& resX, const size_t& resY);

            /// @brief Once you have sorted out what will be the render target resolution, pass this information to PresenZ.
            /// It will set up its blocking mode accordingly.
            /// @param[in] params The resolution parameters.
            /// @return True if successful at setting value.
            presenz_plugin_sdk_EXPORT bool PzSetRenderingResolutionParameters(const PzResolutionParam& params);

            /// @brief If you are in blocked mode: you will have to specify which block you are currently rendering to PresenZ.
            /// @param[in] blockIndex The index of the current block.
            /// @return True if successful at setting value.
            presenz_plugin_sdk_EXPORT bool PzSetCurrentBlockIndex(const size_t& blockIndex);

            /// @brief Add a thread lock mechanism if the renderer is not thread safe when saving images.
            /// @param[in] threadSafe if true, the writing operator add a thread locking mechanism when writing to files.
            /// @return True if successful at setting value.
            presenz_plugin_sdk_EXPORT bool PzSetOutputThreadSafety(const bool& threadSafe);

            /// @brief Set it to false if you are not using the PresenZ internal bucket system.
            /// @param[in] state if true, the internal bucket system will be used.
            /// @return True if successful at setting value.
            presenz_plugin_sdk_EXPORT bool PzSetPresenZBucket(const bool& state);

            /// @brief Get ZOV world position.
            /// @return The position of the ZOV in world space.
            presenz_plugin_sdk_EXPORT NozPoint PzGetZOVWorldPosition();

            /// @brief Get camera to world transformation matrix.
            /// @return The 4x4 camera to world matrix.
            presenz_plugin_sdk_EXPORT NozMatrix PzGetCamToWorldMatrix();

            /// @brief Get world to camera transformation matrix.
            /// @return The 4x4 world to camera matrix.
            presenz_plugin_sdk_EXPORT NozMatrix PzGetWorldToCamMatrix();


            /// @brief Set the Cryptomatte AOVs we want to output.
            /// @param[in] objects Cryptomatte for objects
            /// @param[in] materials Cryptomatte for materials
            /// @param[in] assets Cryptomatte for assets
            /// @return True if successful at setting value.
            presenz_plugin_sdk_EXPORT bool PzSetCryptomatte(const bool& objects, const bool& materials, const bool& assets, const int& objDepth, const int& matDepth, const int& assetDepth);

            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////

            /// @brief PzPhaseBegin methods must be invoked before rendering starts and PzPhaseTerminate must be invoked
            /// after that render has ended. 
            /// Note: In some cases, you don't need to write the final results to disk. We use this mode when the 
            /// results have already been sent through the network.
            enum TerminatePhaseOptions {
                /// Don't write results to disk
                SKIP_DISK_IO = 0,
                /// Write results to disk
                WRITE_TO_DISC = 1
            };

            /// @brief After initialization and once you have invoked all the necessary Setters (see above).
            /// You invoke PzPhaseBegin once the engine is ready to start rendering.
            /// @return True if successful.
            presenz_plugin_sdk_EXPORT bool PzPhaseBegin();

            /// @brief Once rendering is finishing, PzPhaseTerminate has to be invoked. Regarding TerminatePhaseOptions argument,
            /// in the case of distributed rendering: you may not need to have the data saved locally (they were already forwarded to central server).
            /// @param[in] option Specifies whether writing to disk is necessary (default vale is WRITE_TO_DISC).
            /// @return True if successful.
            presenz_plugin_sdk_EXPORT bool PzPhaseTerminate(const TerminatePhaseOptions& option = WRITE_TO_DISC);


            /// @brief log details on the memory usage peak recorded.
            /// Memory recordings are done by PresenZ after, Init Phase, Region Done, Terminate Phase, and Clear.  
            presenz_plugin_sdk_EXPORT void PzLogMemoryUsageRecordedPeak();

            /// @brief return the peak memory usage in Bytes
            presenz_plugin_sdk_EXPORT size_t PzGetMemoryUsageRecordedPeak();

            /// @brief return the current memory usage in Bytes
            presenz_plugin_sdk_EXPORT size_t PzGetCurrentMemoryUsage();


            /// \}
        }// End namespace PRESENZ_VERSION_NS
        using namespace PRESENZ_VERSION_NS;
    } // End namespace 
} // End namespace PresenZ

#endif
