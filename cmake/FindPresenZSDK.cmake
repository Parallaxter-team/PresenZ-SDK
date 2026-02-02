# FindPresenZSDK.cmake
#
# Looks for a PresenZ SDK folder in: ${CMAKE_CURRENT_SOURCE_DIR}/sdk
# Expected structure: <root>/{include,lib,bin}
#
# Variables set on success:
#   PRESENZSDK_FOUND
#   PRESENZSDK_ROOT
#   PRESENZSDK_INCLUDE_DIR
#   PRESENZSDK_LIB_DIR
#   PRESENZSDK_BIN_DIR
#   PRESENZSDK_LIBRARIES        # full paths to libs found in lib/
#   PRESENZSDK_VERSION          # parsed from folder name "PresenZ<version>..."
#
# Target:
#   PresenZ::SDK (INTERFACE)    # includes + links to the libraries found
#
# Override search:
#   -D PRESENZSDK_ROOT="C:/path/to/PresenZ<version>_..._Windows"

include_guard(GLOBAL)

# Allow manual override
set(_PRESENZ_CANDIDATE_ROOTS "")
if(PRESENZSDK_ROOT)
  list(APPEND _PRESENZ_CANDIDATE_ROOTS "${PRESENZSDK_ROOT}")
endif()

# Auto-discover in repo's current source dir
set(_sdk_base "${CMAKE_SOURCE_DIR}/sdk")
if(EXISTS "${_sdk_base}")
  file(GLOB _presenz_dirs LIST_DIRECTORIES true "${_sdk_base}/PresenZ*")
  foreach(_d IN LISTS _presenz_dirs)
    if(IS_DIRECTORY "${_d}" AND
       IS_DIRECTORY "${_d}/include" AND
       IS_DIRECTORY "${_d}/lib" AND
       IS_DIRECTORY "${_d}/bin")
      list(APPEND _PRESENZ_CANDIDATE_ROOTS "${_d}")
    endif()
  endforeach()
endif()

# If no candidates, bail early
if(NOT _PRESENZ_CANDIDATE_ROOTS)
  set(PRESENZSDK_FOUND FALSE)
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(PresenZSDK
    REQUIRED_VARS PRESENZSDK_ROOT PRESENZSDK_INCLUDE_DIR PRESENZSDK_LIBRARIES
    FAIL_MESSAGE "No PresenZ SDK found in ${_sdk_base}. Set PRESENZSDK_ROOT manually.")
  return()
endif()

# Choose the "best" candidate by highest version parsed from directory name.
# Pattern: PresenZ<version>_... e.g. "PresenZ4.1.2_release_CAPI_Build266_9fd5a33_Windows"
set(_best_root "")
set(_best_ver  "")

foreach(_cand IN LISTS _PRESENZ_CANDIDATE_ROOTS)
  set(_ver "")

  # Try the leaf name first, then (only if needed) the full path.
  set(_match_sources "")
  get_filename_component(_dir_name "${_cand}" NAME)
  list(APPEND _match_sources "${_dir_name}" "${_cand}")

  foreach(_src IN LISTS _match_sources)
    # Require PresenZ followed by OPTIONAL short separators and then digits.
    # This avoids matching "presenz-authoring...vs2022".
    # Examples that match: PresenZ1.2.3, PresenZ-1.2.3, PresenZ_1.2
    # Examples that DON'T match: presenz-authoring_build_vs2022
    string(REGEX MATCH "[Pp]resen[Zz][-_. ]*([0-9]+(\\.[0-9]+)*)" _m "${_src}")
    if(CMAKE_MATCH_COUNT GREATER 0)
      set(_ver "${CMAKE_MATCH_1}")
      break()
    endif()
  endforeach()

  if(NOT _best_root)
    set(_best_root "${_cand}")
    set(_best_ver  "${_ver}")
  else()
    if(_ver AND _best_ver)
      if(_ver VERSION_GREATER _best_ver)
        set(_best_root "${_cand}")
        set(_best_ver  "${_ver}")
      endif()
    elseif(_ver AND NOT _best_ver)
      # Prefer one with a version over one without
      set(_best_root "${_cand}")
      set(_best_ver  "${_ver}")
    endif()
  endif()
endforeach()



# Finalize selection
set(PRESENZSDK_ROOT        "${_best_root}"            CACHE PATH "PresenZ SDK root" FORCE)
set(PRESENZSDK_VERSION     "${_best_ver}"             CACHE STRING "PresenZ SDK version" FORCE)
set(PRESENZSDK_INCLUDE_DIR "${PRESENZSDK_ROOT}/include" CACHE PATH "" FORCE)
set(PRESENZSDK_LIB_DIR     "${PRESENZSDK_ROOT}/lib"     CACHE PATH "" FORCE)
set(PRESENZSDK_BIN_DIR     "${PRESENZSDK_ROOT}/bin"     CACHE PATH "" FORCE)

# Collect libraries cross-platform (Windows/.lib, Unix/.a/.so, macOS/.dylib)
set(_lib_globs
  "${PRESENZSDK_LIB_DIR}/*PresenZ.lib"
  "${PRESENZSDK_LIB_DIR}/*PresenZ.a"
  "${PRESENZSDK_LIB_DIR}/*PresenZ.so"
  "${PRESENZSDK_LIB_DIR}/*PresenZ.dylib"
)
set(PRESENZSDK_LIBRARIES "")
foreach(_g IN LISTS _lib_globs)
  file(GLOB _found_libs "${_g}")
  list(APPEND PRESENZSDK_LIBRARIES ${_found_libs})
endforeach()

list(REMOVE_DUPLICATES PRESENZSDK_LIBRARIES)


set(_binary_lib_globs
  "${PRESENZSDK_LIB_DIR}/presenz_*.lib"
  "${PRESENZSDK_LIB_DIR}/presenz_*.a"
  "${PRESENZSDK_LIB_DIR}/presenz_*.so"
  "${PRESENZSDK_LIB_DIR}/presenz_*.dylib"
  "${PRESENZSDK_LIB_DIR}/*blosc.lib"
  "${PRESENZSDK_LIB_DIR}/*blosc.a"
  "${PRESENZSDK_LIB_DIR}/*blosc.so"
  "${PRESENZSDK_LIB_DIR}/*blosc.dylib"  
)

# Handle-result reporting
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PresenZSDK
  REQUIRED_VARS PRESENZSDK_ROOT PRESENZSDK_INCLUDE_DIR PRESENZSDK_LIBRARIES
  VERSION_VAR  PRESENZSDK_VERSION
)

# Helper to stamp SDK runtime props onto a target
function(presenz_sdk_set_runtime_props tgt bin_dir)
  # default, can be overridden via cache if your name differs
  set(_rt "")
  if(WIN32)
    set(_rt "presenz.dll")
    # If actual file differs, allow override:
    set(PRESENZ_SDK_RUNTIME_NAME_WIN "${_rt}" CACHE STRING "Override SDK runtime name on Windows")
    set(_rt "${PRESENZ_SDK_RUNTIME_NAME_WIN}")
  elseif(APPLE)
    set(_rt "libPresenZ.dylib")
    set(PRESENZ_SDK_RUNTIME_NAME_MAC "${_rt}" CACHE STRING "Override SDK runtime name on macOS")
    set(_rt "${PRESENZ_SDK_RUNTIME_NAME_MAC}")
  else()
    set(_rt "libPresenZ.so")
    set(PRESENZ_SDK_RUNTIME_NAME_LINUX "${_rt}" CACHE STRING "Override SDK runtime name on Linux")
    set(_rt "${PRESENZ_SDK_RUNTIME_NAME_LINUX}")
  endif()

  # If the expected name isn't present, try to auto-detect one candidate
  set(_rt_path "${bin_dir}/${_rt}")
  if(NOT EXISTS "${_rt_path}")
    if(WIN32)
      file(GLOB _cand "${bin_dir}/presenz*.dll")
    elseif(APPLE)
      file(GLOB _cand "${bin_dir}/lib[Pp]resen[Zz]*.dylib")
    else()
      file(GLOB _cand "${bin_dir}/lib[Pp]resen[Zz]*.so")
    endif()
    list(LENGTH _cand _n)
    if(_n GREATER 0)
      list(GET _cand 0 _rt_path)
      get_filename_component(_rt "${_rt_path}" NAME)
    endif()
  endif()

  # Stamp properties on the *real* target (alias is fine to pass in)
  set_property(TARGET ${tgt} PROPERTY PRESENZSDK_BIN_DIR       "${bin_dir}")
  set_property(TARGET ${tgt} PROPERTY PRESENZSDK_RUNTIME_NAME  "${_rt}")
  set_property(TARGET ${tgt} PROPERTY PRESENZSDK_RUNTIME_PATH  "${_rt_path}")
endfunction()


# IMPORTANT: the variable set by the handler is PresenZSDK_FOUND (case-sensitive)
if(PresenZSDK_FOUND)
  if(NOT TARGET PresenZ::SDK)
    add_library(PresenZ::SDK INTERFACE IMPORTED)
	target_include_directories(PresenZ::SDK INTERFACE
	  "${PRESENZSDK_INCLUDE_DIR}"	)
	presenz_sdk_set_runtime_props(PresenZ::SDK "${PRESENZSDK_BIN_DIR}")
    if(PRESENZSDK_LIBRARIES)
      target_link_libraries(PresenZ::SDK INTERFACE ${PRESENZSDK_LIBRARIES})
    endif()
    if(WIN32)
      # Optional hints for consumers
      set_target_properties(PresenZ::SDK PROPERTIES
        INTERFACE_LINK_DIRECTORIES "${PRESENZSDK_LIB_DIR}"
      )
      set(PRESENZSDK_RUNTIME_PATH_HINT "${PRESENZSDK_BIN_DIR}" CACHE PATH
          "Add to PATH to run with PresenZ DLLs")
    endif()
  endif()
endif()
