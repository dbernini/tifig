project (TifigJNI)

cmake_minimum_required (VERSION 3.5)

find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include(UseJava)

enable_testing()
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")
set(JAVA_JNI_PACKAGE org.monostream)

add_jar(Tifig org/monostream/Tifig.java)

get_target_property(_jarFile Tifig JAR_FILE)
get_target_property(_classDir Tifig CLASSDIR)

set (_stubDir "${CMAKE_CURRENT_BINARY_DIR}")
add_custom_command(
    OUTPUT TifigJNI.h
    COMMAND ${Java_JAVAH_EXECUTABLE} -verbose
        -classpath ${_classDir}
        -o ${_stubDir}/TifigJNI.h
        ${JAVA_JNI_PACKAGE}.Tifig
    DEPENDS Tifig
    )

set(LIBTIFIG_DIR ${PROJECT_SOURCE_DIR}/../lib/tifig)
add_subdirectory(${LIBTIFIG_DIR} ./tifig)

set(LIBHEIF_DIR ${PROJECT_SOURCE_DIR}/../lib/heif)
add_subdirectory(${LIBHEIF_DIR} ./heif)

include_directories(${LIBTIFIG_DIR})


include_directories(${JNI_INCLUDE_DIRS} ${_classDir} ${_stubDir})
add_library(tifig_jni SHARED TifigJNI.cpp TifigJNI.h)

target_link_libraries(tifig_jni ${JNI_LIBRARIES} tifiglib heifreader)

add_test(NAME TestTifigJNI
    COMMAND ${Java_JAVA_EXECUTABLE}
    -Djava.library.path=${CMAKE_CURRENT_BINARY_DIR}
    -cp ${_jarFile} ${JAVA_JNI_PACKAGE}.tifig)
