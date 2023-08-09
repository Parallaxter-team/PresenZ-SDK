
/**
* Various useful constants
*/

#pragma once

#define NOZ_PI                 (3.1415926535897931f)   
#define NOZ_PITIMES2           (6.2831853071795862f)  /**< 2 * pi                 */
#define NOZ_PIOVER2            (1.5707963267948966f)
#define NOZ_E                  (2.7182818284590452f) 
#define NOZ_DTOR               (0.0174532925199433f)   /**< Degrees to radians      */
#define NOZ_RTOD               (57.295779513082323f)   /**< Radians to degrees      */
#define NOZ_SQRT2               (1.4142135623730951f)  /**< 2.0 square root          */        
#define NOZ_EPSILON            (1.0e-4f)             
#define NOZ_BIG                (1.0e12f)             
#define NOZ_INFINITE           (1.0e30f) 
#define NOZ_MAXRAYBACK         (1.0e6f)                //1000000; //1 milion units (e^6) was chosen as the max distance from which to cast a ray back, because at that point there is no parallax anymore   

/*\}*/


typedef char               NozInt8;     /**<  8-bit signed integer   */
typedef short              NozInt16;    /**< 16-bit signed integer   */
typedef int                NozInt32;    /**< 32-bit signed integer   */
typedef signed long long   NozInt64;    /**< 64-bit signed integer   */
typedef unsigned char      NozByte;     /**<  8-bit unsigned integer (same as \ref NozUInt8) */
typedef unsigned char      NozUInt8;    /**<  8-bit unsigned integer */
typedef unsigned short     NozUInt16;   /**< 16-bit unsigned integer */
typedef unsigned int       NozUInt32;   /**< 32-bit unsigned integer */
typedef unsigned long long NozUInt64;   /**< 64-bit unsigned integer */