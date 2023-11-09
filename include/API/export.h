#ifndef _presenz_sdk_DLLDEFINES_H_
#define _presenz_sdk_DLLDEFINES_H_

#define H_VAL(str) #str
#define H_TOSTRING(str) H_VAL(str)

#define PRESENZ_FULL_VERSION "3.0.3"

#define PRESENZ_MAJOR_VERSION 3
#define PRESENZ_MINOR_VERSION 0
#define PRESENZ_PATCH_VERSION 3

#ifndef PRESENZ_VERSION_NS 
#define PRESENZ_VERSION_NS v3_0
#endif

#if defined(PRESENZ_SDK_DLL)
    #if defined(presenz_plugin_sdk_EXPORTS)
        #define presenz_plugin_sdk_EXPORT __declspec(dllexport)
        #define presenz_plugin_sdk_PYEXPORT extern "C" __declspec(dllexport)
    #else
        #define presenz_plugin_sdk_EXPORT __declspec(dllimport)
        #define presenz_plugin_sdk_PYEXPORT extern "C" __declspec(dllimport)
    #endif
    #define presenz_plugin_sdk_EXPORT_CONST
#else
    #if defined _WIN32 || defined _WIN64
        #define presenz_plugin_sdk_EXPORT
        #define presenz_plugin_sdk_PYEXPORT
    #else
        #define presenz_plugin_sdk_EXPORT __attribute__ ((visibility ("default")))
        #define presenz_plugin_sdk_PYEXPORT __attribute__ ((visibility ("default")))
    #endif
    #define presenz_plugin_sdk_EXPORT_CONST const
#endif

#endif 
