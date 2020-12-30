project(tifiglib)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

# Needed for heif library from nokia
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-unused-parameter -Wno-unused-variable")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(STATIC_BUILD "Build tifig static")

find_package(PkgConfig)

pkg_check_modules(AVCODEC libavcodec REQUIRED)
pkg_check_modules(AVUTIL libavutil REQUIRED)
pkg_check_modules(SWSCALE libswscale REQUIRED)
pkg_check_modules(VIPS vips-cpp REQUIRED)

if (STATIC_BUILD)
    pkg_check_modules(EXPAT expat REQUIRED)
    set(TIFIG_LDFLAGS
            ${AVCODEC_STATIC_LDFLAGS}
            ${AVUTIL_STATIC_LDFLAGS}
            ${SWSCALE_STATIC_LDFLAGS}
            ${VIPS_STATIC_LDFLAGS}
            ${EXPAT_STATIC_LDFLAGS})
else()
    set(TIFIG_LDFLAGS
            ${AVCODEC_LDFLAGS}
            ${AVUTIL_LDFLAGS}
            ${SWSCALE_LDFLAGS}
            ${VIPS_LDFLAGS})
endif()

set(LIBHEIF_DIR ../heif)

include_directories(${LIBTIFIG_DIR})
include_directories(${LIBHEIF_DIR}/Srcs/common)
include_directories(${LIBHEIF_DIR}/Srcs/reader)

include_directories(${AVCODEC_INCLUDE_DIRS})
include_directories(${AVUTIL_INCLUDE_DIRS})
include_directories(${SWSCALE_INCLUDE_DIRS})
include_directories(${VIPS_INCLUDE_DIRS})


add_library(tifiglib hevc_decode.cpp heif.cpp imaging.cpp loader.cpp tifig.cpp)

target_link_libraries(tifiglib heifreader pthread)
target_link_libraries(tifiglib ${TIFIG_LDFLAGS})
