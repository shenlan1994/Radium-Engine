#ifndef RADIUMENGINE_RA_CORE_HPP_
#define RADIUMENGINE_RA_CORE_HPP_

#include <Core/CoreMacros.hpp>

//#define RELEASE_EIGEN_PLUGIN_PROTECTION_AGAINST_DIRECT_INCLUSION
//#define EIGEN_MATRIX_PLUGIN "Core/Mesh/TopologicalTriMesh/EigenOpenMeshPlugin.h"

/// Defines the correct macro to export dll symbols.
#if defined RA_CORE_EXPORTS
#    define RA_CORE_API DLL_EXPORT
#elif defined RA_CORE_STATIC
#    define RA_CORE_API
#else
#    define RA_CORE_API DLL_IMPORT
#endif

#endif // RADIUMENGINE_RA_CORE_HPP_
