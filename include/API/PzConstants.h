//////////////////////////////////////////////////////////////////////////
// (c) Copyright 2023

/// \file PzConstants.h
// All rights reserved.
#ifndef __PZ_CONSTANTS_H__
#define __PZ_CONSTANTS_H__

namespace PresenZ {
    namespace Logger {
        namespace PRESENZ_VERSION_NS {
            /// @brief Severity log levels for each log line
            enum LogLevel
            {
                LL_Error = 0,               // An error occurred, most likely fatal and PresenZ is unable to continue
                LL_Warning = 1,             // An unexpected event occurred, while not fatal, user should be very cautious about the results
                LL_Info = 2,                // Simple notifications, nothing wrong here
                LL_Debug = 3,               // Notifications used for tracking issues and bugs
                LL_Trace = 4,               // - For internal use
            };

            /// @brief The default mode is CR_NoCarriageReturn, this means that the last carriage return is skipped in the
            /// user callback. Set it to CR_CarriageReturnNeeded if your logger needs a terminal carriage return.
            enum CarriageReturnMode
            {
                CR_NoCarriageReturn = 0,
                CR_CarriageReturnNeeded = 1,
                CR_Ignore = 2
            };


            enum ProgressBarType
            {
                PT_horizontal = 0,
                PT_vertical = 1,
                PT_callback = 2
            };
        }
    }

    namespace DetectSample {
        namespace PRESENZ_VERSION_NS {

            enum DetectSample_transp {
                DST_opaque = 0,
                DST_glass = 1,
                DST_semiTransp = 2
            };
        }
    }

    namespace Phase {
        namespace PRESENZ_VERSION_NS {
            ///@brief TransparencyRenderingType defines the rendering mode of PresenZ, the default mode is PRZ_REGULAR which will not render glass.
            enum TransparencyRenderingType
            {
                /// glass rendering mode is off
                PRZ_REGULAR,
                /// opaque only
                PRZ_OPAQUE,
                /// glass only
                PRZ_TRANSP,
                /// Both, if the renderer support it.		
                PRZ_BOTH
            };
            ///@brief Eye describes for which eye we are rendering, this is used in PresenZ to bend rays correctly.
            enum Eye
            {
                /// render left and right eye
                RC_LeftAndRight = 0,
                /// render left eye
                RC_Left = 1,
                /// render right eye
                RC_Right = 2
            };
            ///@brief Phase defines the rendering phase. 
            ///PresenZ renders in two phases. The first phase is the Detect Phase which determines in which directions we can see.
            ///The second phase is the Render Phase which actually renders the shaders and materials.
            enum Phase
            {
                /// Detection phase
                Detect = 0,
                /// Render phase
                Render = 1,
                /// Detection phase for reflections
                Detect_Reflection = 2,
                /// Detection phase for reflections
                Render_Reflection = 3
            };

            ///@brief Space for point & vector coordinates.
            ///For the function that return a point or a vector, this will define witch space will be used.
            enum Space
            {
                /// camera space.
                Camera = 1,
                /// world space.
                World = 2
            };

            /// @brief RayDerivative computation method. 
            /// use Phase::PzSetRayDerivativeType(enum RayDerivativeType); to tell PresenZ how ray derivatives must be computed.(dDdx and dDdy)
            enum RayDerivativeType
            {
                /// Ray derivatives computations does not take in account the normalization of the ray. ( Arnold type)
                RDT_UNSCALED = 0,
                /// Ray derivatives computations take in account the normalization of the ray to scale the derivatives ( Vray type)
                RDT_SCALED = 1,
            };

            ///@brief for froxtrum rendering only, PresenZ moves the camera Ray origin or uses camera the NearClipPlane 
            enum FroxtrumRayOrigin
            {
                moveCameraOrigin = 1,
                useCameraNearClip = 2
            };

            /// @brief Prevent the detection phase to output duplicated data to the postProcess filters.
            /// no_duplicates should onely be used on nodes which outPut przDetect file and only if they are collecting data from other nodes at runtime.(vray, ditributed Rendering)
            enum DetectionRTFiltering
            {
                no_filter = 0,
                no_duplicates = 1
            };

            enum DetectionSafeGuard
            {
                DSG_warning = (1u << 0),
                DSG_error = (1u << 1),
                DSG_disabled = (1u << 2)
            };

            /// @brief Once parameters have been set, you can register the AOVs you want to PresenZ. AOVType gives the supported AOV types that can be stored. 
            /// These will be stored per pixel in the PrzRender files. 
            enum AOVType
            {
                /// Boolean
                BOOL = 0,
                /// Integer
                INT = 1,
                /// Float
                FLOAT = 2,
                /// RGB
                RGB = 3,
                /// RGBA
                RGBA = 4,
                /// 3D Vector
                VEC = 5,
                /// 2D Vector
                VEC2 = 6,
                /// PresenZ Internal used only on our Buckets 
                PRZ = 7
            };

        }
    }
}
#endif // __PZ_CONSTANTS_H__
