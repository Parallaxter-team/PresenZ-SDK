#ifndef _PzDetectSampleMPAPI_h_
#define _PzDetectSampleMPAPI_h_

#include "export.h"

namespace PresenZ {
namespace DetectSample {
namespace PRESENZ_VERSION_NS {
    
    // Due to the nature of GPU, the ray tracing can’t be performed on GPU one by one and it has to be passed as group.
    // The following functions are used for processing the rays in Batch and then this Batch of rays are passed to GPU together for ray tracing

    /**
     * Get pointer for ray tracing input data
     * This data is prepared inside PresenZ SDK and it is supposed to pass to any GPU ray tracing kits
     */
    presenz_plugin_sdk_EXPORT void* PzDetectGetRtInput();

    /**
     * Get pointer for ray tracing result data
     * The ray tracing results is suppose to pass to this pointer and then it can be used inside PresenZ SDK
     */
    presenz_plugin_sdk_EXPORT void* PzDetectGetRtOutput();

    /**
     * Initialise the processing
     */
    presenz_plugin_sdk_EXPORT void PzDetectInit();

    /**
     * Close the processing
     */
    presenz_plugin_sdk_EXPORT void PzDetectCleanup();

    /**
     * Set the Batch size of rays
     */
    presenz_plugin_sdk_EXPORT void PzDetectSetBatchSize(int bsize);

    /**
     * Processing the Batch of rays
     */
    presenz_plugin_sdk_EXPORT void PzDetectProcess();

    /**
     * In order to improve efficiency, we are trying to parallel the CPU and GPU jobs.
     * While OptiX performs ray tracing test in GPU, PresenZ is proceeding data in CPU.
     * Therefore, there are two data sets inside PresenZ SDK. While one data set is proceeded
     * in PresenZ SDK, the other data set is transferred to OptiX for ray tracing test.
     * Then, the two data sets are swapped for next round of proceeding.
     */
    presenz_plugin_sdk_EXPORT void PzDetectSwap();

    /**
     * Is all Batchs of rays finished and detection work is done?
     * @return true means finished, false otherwise
     */
    presenz_plugin_sdk_EXPORT bool PzDetectIsDone();

    /**
     * Report how many percentage of Batchs of ray has been finished
     * @return percentage from 0% to 100%
     */
    presenz_plugin_sdk_EXPORT double PzDetectGetCurProgress();

}
using namespace PRESENZ_VERSION_NS;
}
}

#endif