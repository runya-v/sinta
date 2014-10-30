# Find the native CEF3 includes and library
#
#  CEF3_INCLUDE_DIR - where to find *.h, etc.
#  CEF3_LIBRARIES   - List of libraries when using CEF3.
#  CEF3_FOUND       - True if CEF3 found.

include(TakeComponent)
find_template(
    COMPONENT_NAME CEF3 
    INCLUDE_NAMES cef_version.h 
    LIB_NAMES libcef.so libffmpegsumo.so
    )
