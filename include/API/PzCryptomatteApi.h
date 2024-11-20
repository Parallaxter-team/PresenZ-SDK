#ifndef _PZCRYPTOMATTEAPI_h_
#define _PZCRYPTOMATTEAPI_h_

#include "PzRenderSampleApi.h"
#include <map>

namespace PresenZ {
namespace Cryptomatte {
namespace PRESENZ_VERSION_NS {

#define PZ_CRYPTO_MAX_STRING_LENGTH 2048

    enum cryptoType {
        object = 0,
        material = 1,
        asset = 2
    };

    

            ///\brief Callback getting the name of an geometry object.
            typedef const char* (*GetNodenameCallback)(void* ptr, void* userData);
            typedef const char* (*GetMaterialnameCallback)(void* ptr, void* userData);
            typedef bool (*IsMaterialCacheableCallback)(void* ptr, void* userData);


            struct CryptoMattetInterface
            {
                void* objPtr = nullptr;
                void* userdata = nullptr;
                GetNodenameCallback getNodeName = nullptr;
                GetMaterialnameCallback getMaterialName = nullptr;
                IsMaterialCacheableCallback isMaterialCacheable = nullptr;

                CryptoMattetInterface(void *objPtr, void* userdata, GetNodenameCallback nodeNameCb, GetMaterialnameCallback materialNameCb, IsMaterialCacheableCallback isMaterialCacheableCb)
                    : objPtr(objPtr), userdata(userdata), getNodeName(nodeNameCb), getMaterialName(materialNameCb), isMaterialCacheable(isMaterialCacheableCb) {}
            };


            presenz_plugin_sdk_EXPORT void PzProcessNode(CryptoMattetInterface* intf, const size_t& threadIndex, float& nsp_hash_clr, float& obj_hash_clr, float& mat_hash_clr);

            /// @brief Function to get the active Cryptomattes AOV in presenZ.  
            presenz_plugin_sdk_EXPORT void PzGetActiveCryptomatte(bool& objects, bool& materials, bool& assets);

            presenz_plugin_sdk_EXPORT void PzSetSampleCrypto(PresenZ::RenderSample::PzRenderSample& sample, const cryptoType& type, const float& value);

            presenz_plugin_sdk_EXPORT void PzAddObjectToManifest(const char* name);
            presenz_plugin_sdk_EXPORT void PzAddMaterialToManifest(const char* name);
}
using namespace PRESENZ_VERSION_NS;
}
}
#endif