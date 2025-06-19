//////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.
// All rights reserved.
#ifndef _PzBlockAPI_h_
#define _PzBlockAPI_h_

#include "export.h"

/// \file PzBlockApi.h


namespace PresenZ {
namespace Block {
namespace PRESENZ_VERSION_NS {

/// \defgroup block Block interface
/// \brief Queries to PresenZ about resolution properties for rendering the second phase.
///  \details The second phase (a.k.a. the rendering phase) might need more than one full screen render depending the complexity of 
/// the geometry. Screen renders are called blocks. Depending the target resolution set up for your image, the number of blocks 
/// may vary. 
///
/// PzGetBlockCountFromRenderingResolution() with the provided desired resolution will compute the number of blocks needed 
/// to shade every points of the final PresenZ image. 
///
/// Alternatively it is possible to enforce only one render, but then the renderer will have to adapt the output resolution to
/// fit all pixels on the same render target. For this purpose, you should invoke PzGetRenderingResolutionFromBlockCount() with a
/// blockcount = 1. 
///
/// We strongly advise the former solution, specially if your geometry/overall aesthetics (i.e.: displacement map...) may vary 
/// depending the target resolution. Set The resolution resX/resY to what is optimal for the renderer and let the pixels be
/// shaded.
/// \{

/// @brief Read the detect file with the path set in the PresenZ context and with the rendering resolution, 
/// @return the number of blocks needed for the render Phase. Or zero in case of an error.
presenz_plugin_sdk_EXPORT size_t PzGetBlockCountFromRenderingResolution();

/// @brief Read the detect file in parameter and according to the given resolution,
/// @param pathToDetectFile full file path to detection przDetect file
/// @param resX renderer target horizontal resolution
/// @param resY renderer target vertical resolution
/// @return the number of blocks of rendering resolution needed for the render Phase. Or zero in case of error.
presenz_plugin_sdk_EXPORT size_t PzGetBlockCountFromRenderingResolution(const char * pathToDetectFile, const size_t &resX, const size_t &resY);

/// @brief Read the detect file with the path set in the PresenZ Context 
/// @param pathToDetectFile full file path to detection przDetect file
/// @param blockcount the number of block
/// @param resX will receive the needed horizontal resolution for 
/// @param resY will receive the needed vertical resolution for 
/// @return true with the rendering resolution needed for the rendering phase, false in case of error.
presenz_plugin_sdk_EXPORT bool PzGetRenderingResolutionFromBlockCount(const char * pathToDetectFile, const size_t &blockcount, size_t &resX, size_t &resY);

/// @brief Get the full path to the first pass detection file (in case that you access it and transfer it over the network).
/// @return path to the PresenZ context
presenz_plugin_sdk_EXPORT std::string PzGetDetectPhaseFileFromPresenZContext();

/// @brief On distributed renderer, you may want to overwrite the location of the first pass detection file.
/// @param fileName full file path to the detection przDetect file that must be using for rendering
presenz_plugin_sdk_EXPORT void PzSetDetectPhaseOverride(const std::string& fileName);

/// \}

}
using namespace PRESENZ_VERSION_NS;
}
}

#endif