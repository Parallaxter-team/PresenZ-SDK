//////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.
// All rights reserved.

/// \file PzBucketApi.h

#ifndef _PzbucketAPI_h_
#define _PzbucketAPI_h_

#include "PzExport.h"
#include <vector>
#include "PzRenderSampleApi.h"
#include "PzDetectSampleApi.h"

namespace PresenZ {
namespace BinIO {
namespace PRESENZ_VERSION_NS {
	
/// \defgroup bucketAPI Bucket interface
/// \brief Bucket system support: buckets are regions of the target image that are processed independently.
/// \details Buckets are a common concept in ray tracers: instead of rendering the full image pixel per pixel, the 
/// image is subdivided into smaller chunks (=bucket). The Ray tracer will notify every time a bucket is 
/// started. It will also notify when all the samples of a bucket are done so that the data can be 
/// processed and disposed.
/// \section Intro Initialization/Termination
/// When a fresh bucket is started, PzInitBucket() should be invoked with the corresponding image region. 
/// PresenZ will prepare its internal structures for the newly incoming pixel data.
///
/// Similarly, when a bucket is done, PzProcessBucketFlushToFile() should be invoked on this file region. 
/// PresenZ will write all the rendered data into a temporary file. When the image is finished, the 
/// temporary file will be read entirely and the final output file will be generated.
///
/// \section distributed Distributed rendering
///
/// Some ray tracers send raw bucket data through the network from distributed worker rendering nodes to 
/// the main node. The result is then collected in the main node. PzBucketFlushToMemory() will serialize 
/// the bucket into memory. PzProcessBucketGetBufferSize() will provide how much memory is needed for this
/// operation. Similarly, PzFlushMemoryBufferToFile() will process serialized bucket data and write it to 
/// the temporary file. 
///
/// \section ThreadSafety Thread safety issue 
///
/// In most ray tracers, buckets are assigned to one single thread. Each thread computes the pixels 
/// independently. For this reason, there's no threading safety inside a PresenZ bucket. If, for any 
/// reason, multiple threads can access the same bucket, then the client application must handle the 
/// mutual exclusivity before accessing the bucket.
///
/// \section NoBucketSystem If there is no bucket system in your renderer
/// 
/// If a ray tracer does not use buckets, then the PresenZ plugin should call PzInitBucket() with the full 
/// resolution image. When the rendering is finished, PzProcessBucketFlushToFile() is then similarly invoked.
///
/// If you don't want to have the full image data in memory. You can arbitrarily split the image into 
/// chunks. Invoke PzInitBucket() when a part is started and PzProcessBucketFlushToFile() when a part is 
/// finished.	
/// \{


/// @brief Initialize a bucket (attached to a bucketId) that will contain pixels for the Region [x0,y0;x1,y1].
/// @param[in] bucketId Identifier (number) of the bucket
/// @param[in] x0 top left x coordinate of the screen region corresponding to the bucket
/// @param[in] y0 top left y coordinate of the screen region corresponding to the bucket
/// @param[in] x1 bottom right x coordinate of the screen region corresponding to the bucket
/// @param[in] y1 bottom right y coordinate of the screen region corresponding to the bucket
presenz_plugin_sdk_EXPORT void PzInitBucket(const size_t &bucketId, const int &x0, const int &y0, const int &x1, const int &y1);

/// @brief Process the samples in the bucket into pixels and flush the result to the disk, returns true if successful.
/// @param[in] bucketId Identifier of the bucket that can be sent to disk and disposed
/// @return true if everything went fine
presenz_plugin_sdk_EXPORT bool PzProcessBucketFlushToFile(const size_t &bucketId);

/// @brief Process the samples in the bucket into pixels and flush the result to the disk, returns true if successful.
/// @param[in] x0 top left x coordinate of the screen region corresponding to the bucket
/// @param[in] y0 top left y coordinate of the screen region corresponding to the bucket
/// @param[in] x1 bottom right x coordinate of the screen region corresponding to the bucket
/// @param[in] y1 bottom right y coordinate of the screen region corresponding to the bucket
/// @return true if everything went fine
presenz_plugin_sdk_EXPORT bool PzProcessBucketFlushToFile(const int &x0, const int &y0, const int &x1, const int &y1);

/// @brief Flush the result to the disk, returns true if successful.
/// @param[in] detections samples returned by the function PzProcessDetectSample, using the SaveDataCallBack callback
/// @param[in] count number of samples in the detections array
/// @return true if everything went fine
presenz_plugin_sdk_EXPORT bool PzFlushSamplesToFile(const PresenZ::DetectSample::SaveDataStructure* detections, size_t count);

/// @brief Flush the result to the disk, returns true if successful.
/// @param[in] samples filtered samples returned by the function PzFilterRenderSample
/// @param[in] count number of samples in the samples array
/// @return true if everything went fine
presenz_plugin_sdk_EXPORT bool PzFlushSamplesToFile(const PresenZ::RenderSample::PzFilteredSample* samples, size_t count);

/// @brief This will go through all buckets and write any contained data to disk. Use this if the application is 
/// terminating in an unexpected way.
presenz_plugin_sdk_EXPORT void PzProcessAllBucketsToFile();

//////////////////////////////////////////////////////////////////////////

/// @brief Specify how much memory you need to store the processed bucket memory data.
/// @param[in] bucketId Identifier of the bucket that can be sent to disk and disposed
/// @return Memory needed to serialize the bucket data, returns -1 in case of an error.
presenz_plugin_sdk_EXPORT int PzProcessBucketGetBufferSize(const size_t &bucketId);

/// @brief Specify how much memory you need to store the processed bucket memory data. 
/// @param[in] x0 top left x coordinate of the screen region corresponding to the bucket
/// @param[in] y0 top left y coordinate of the screen region corresponding to the bucket
/// @param[in] x1 bottom right x coordinate of the screen region corresponding to the bucket
/// @param[in] y1 bottom right y coordinate of the screen region corresponding to the bucket
/// @return Memory needed to serialize the bucket data, returns -1 in case of an error.
presenz_plugin_sdk_EXPORT int PzProcessBucketGetBufferSize(const int &x0, const int &y0, const int &x1, const int &y1);

/// @brief Write the content of the processed bucket and write the result into a buffer.
/// @param[in] buffer Target memory that will contain the serialized data
/// @param[in] bufferSize Size of target memory, should be the size of PzProcessBucketGetBufferSize
/// @param[in] bucketId Identifier of the bucket that can be sent to disk and disposed
/// @return True if data were correctly serialized into buffer
presenz_plugin_sdk_EXPORT bool PzBucketFlushToMemory(void *buffer, const size_t &bufferSize, size_t &bucketId);

/// @brief Write the content of the processed bucket and write the result into a buffer.
/// @param[in] buffer Target memory that will contain the serialized data
/// @param[in] bufferSize Size of target memory, should be the size of PzProcessBucketGetBufferSize
/// @param[in] x0 top left x coordinate of the screen region corresponding to the bucket
/// @param[in] y0 top left y coordinate of the screen region corresponding to the bucket
/// @param[in] x1 bottom right x coordinate of the screen region corresponding to the bucket
/// @param[in] y1 bottom right y coordinate of the screen region corresponding to the bucket
/// @return True if data were correctly serialized into buffer
presenz_plugin_sdk_EXPORT bool PzBucketFlushToMemory(void *buffer, const size_t &bufferSize, const int &x0, const int &y0, const int &x1, const int &y1);

/// @brief De-serialized the data and process the buffer internally.
/// @param[in] buffer Target memory that will contain the serialized data
/// @param[in] bufferSize Size of buffer in memory.
/// @return True if data were correctly deserialized, returns false if the buffer is invalid or too small.
presenz_plugin_sdk_EXPORT bool PzFlushMemoryBufferToFile(const void *buffer, const size_t &bufferSize);

/// \}

}
using namespace PRESENZ_VERSION_NS;
}
}

#endif
