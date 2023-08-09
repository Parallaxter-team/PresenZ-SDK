#ifndef _PresenZ_Utility_define_h_
#define _PresenZ_Utility_define_h_

#ifndef PRESENZ_VERSION_NS 
#define PRESENZ_VERSION_NS v3_0
#endif

#include <sstream>
#include <exception>
#include <string>


namespace PresenZ {
namespace Util {
namespace PRESENZ_VERSION_NS {

	///@brief Rendered ID. Please contact us to add officially yours in the list.
    enum class RenderingEngineId {
		/// Undefined renderer
        UNDEFINED = 0,
		/// VRAY
        VRAY = 1,
		/// PRMAN
        RENDERMAN = 2,
		/// Corona
        CORONA = 3,
		/// Houdini output
        HOUDINI = 4,
		/// Arnold
        ARNOLD = 5,
        // Vray Japan
		VRAY_JAPAN = 6,
		/// For developping
        PRESENZ_DEVELOP = 49,
		/// For debugging
        PRESENZ_DEBUG = 50
    };

/// @brief Exception handler
class Exception : public std::string, public std::exception
{
public:
    Exception() throw() : std::string(""), std::exception() {}
/// exception
    explicit Exception(const std::string &str) throw()
        : std::string(str), std::exception() {}
/// exception
    Exception(const Exception &exc) throw()
        : std::string(exc.c_str()), std::exception() {}
    virtual ~Exception() throw() {}
/// exception
    virtual const char *what() const throw() { return c_str(); }
};


#define PRESENZ_THROW( TEXT )                         \
                                                      \
{                                                     \
    std::stringstream sstr;                           \
    sstr << TEXT;                                     \
    PresenZ::Util::Exception exc( sstr.str() );       \
    throw( exc );                                     \


} 
using namespace PRESENZ_VERSION_NS;
} 
} 


#endif
