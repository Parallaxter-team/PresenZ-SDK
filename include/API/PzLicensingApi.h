#ifndef _PZLICENSINGAPI_h_
#define _PZLICENSINGAPI_h_

#include "PzExport.h"

namespace PresenZ {
namespace Licensing {
namespace PRESENZ_VERSION_NS {

/// @brief Function to acquire a PresenZ License. 
/// @return True if the license is acquired.
presenz_plugin_sdk_EXPORT bool PzCheckoutLicense();

/// @brief Function to return a PresenZ License.
/// @return True if the license is returned.
presenz_plugin_sdk_EXPORT bool PzCheckinLicense();

/// @brief Function to check the current state of the PresenZ license. Can only be valid if called between a PzCheckoutLicense and a PzCheckinLicense.
/// @return True if the license is valid.
presenz_plugin_sdk_EXPORT bool PzCheckLicense();

presenz_plugin_sdk_PYEXPORT bool PzTestLicense(char* outBuffer, int bufferSize);

}
using namespace PRESENZ_VERSION_NS;
}
}
#endif