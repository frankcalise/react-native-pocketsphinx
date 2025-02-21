project(NitroPocketSphinx)
cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME NitroPocketSphinx)
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 20)

# Define C++ library and add all sources
add_library(
        ${PACKAGE_NAME}
        SHARED 
	src/main/cpp/cpp-adapter.cpp
	../cpp/HybridPocketSphinx.cpp
	../cpp/HybridPocketSphinx.hpp
)

# Add Nitrogen specs :)
include(${CMAKE_SOURCE_DIR}/../nitrogen/generated/android/NitroPocketSphinx+autolinking.cmake)

# Set up local includes
include_directories(
        "src/main/cpp"
        "../cpp"
)

# 1. Create imported target representing precompiled library
# 2. Assign properties to the target, the file location for the precompiled binary
# 3. Include the library headers
# 4. Link the library to the target
cmake_path(SET LIBPOCKETSPHINX ${CMAKE_CURRENT_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libpocketsphinx.so NORMALIZE)
add_library(libpocketsphinx SHARED IMPORTED)
set_target_properties(libpocketsphinx PROPERTIES IMPORTED_LOCATION ${LIBPOCKETSPHINX})

target_include_directories(
        ${PACKAGE_NAME}
        PRIVATE
        ../cpp/libpocketsphinx
        ../cpp/libpocketsphinx/pocketsphinx
)

find_library(LOG_LIB log)

# Link all libraries together
target_link_libraries(
        ${PACKAGE_NAME}
        ${LOG_LIB}
        android                                   # <-- Android core
        libpocketsphinx                     # <-- PocketSphinx
)
