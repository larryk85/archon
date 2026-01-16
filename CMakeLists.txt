cmake_minimum_required(VERSION 3.18)

project(archon VERSION 1.0.0.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads)
link_libraries(Threads::Threads)

include(CMakeDependentOption)
option(ARCHON_ENABLE_TESTS    "Enable building of unit tests" ON)
option(ARCHON_ENABLE_DOCS     "Enable creation of the documentation" ON)
option(ARCHON_ENABLE_INSTALL  "Enable installation" ON)
option(ARCHON_ENABLE_PEDANTIC "Enable pedantic warnings" OFF)

message( STATUS "Building archon v${archon_VERSION}..." )
if (MSVC)
   if (CMAKE_SIZEOF_VOID_P EQUAL 8)
      add_compile_definitions(_AMD64_)
   else()
      add_compile_definitions(_X86_)
   endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(archon INTERFACE)

target_include_directories(archon INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
   $<INSTALL_INTERFACE:include>)

if(ARCHON_ENABLE_PEDANTIC)
   target_compile_options(archon INTERFACE
      $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Werror>
      $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic -Werror>)
endif()

target_compile_options(archon INTERFACE
   $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>)

target_compile_definitions(archon INTERFACE
   $<$<CONFIG:Debug>:archon_DEBUG>
   $<$<CONFIG:Release>:archon_RELEASE>
   $<$<CONFIG:RelWithDebInfo>:archon_RELWITHDEBINFO>
   $<$<CONFIG:MinSizeRel>:archon_MINSIZEREL>)

add_library(archon::archon ALIAS archon)

include(FetchContent)
if(ARCHON_ENABLE_TESTS)
   FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2
      GIT_TAG v3.6.0
   )

   FetchContent_GetProperties(Catch2)
   if (NOT Catch2_POPULATED)
      FetchContent_MakeAvailable(Catch2)
      list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
   endif()

   include(CTest)
   include(Catch)

   enable_testing()
   add_subdirectory(tests)
endif()

if(archon_ENABLE_DOCS)
   #archon_generate_doxygen_docs()
endif()

include(GNUInstallDirs)

# ##################################################################################################
# Configure version info.
# ##################################################################################################
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/archon-config-version.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/archon-config-version.cmake @ONLY)

# ##################################################################################################
# Installation.
# ##################################################################################################
if(ARCHON_ENABLE_INSTALL)
   include(CMakePackageConfigHelpers)
   include(GNUInstallDirs)

   message(STATUS "Installing archon ...")
   set(ARCHON_INCLUDE_DIRS ${CMAKE_INSTALL_INCLUDEDIR})
   configure_package_config_file(cmake/archon-config.cmake.in
      ${CMAKE_CURRENT_BINARY_DIR}/archon-config.cmake
      INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/archon
      PATH_VARS ARCHON_INCLUDE_DIRS
   )
   write_basic_package_version_file(
      ${CMAKE_CURRENT_BINARY_DIR}/archon-config-version.cmake
      VERSION ${archon_VERSION}
      COMPATIBILITY SameMajorVersion
   )

   install(TARGETS archon
           EXPORT archon-targets
           LIBRARY
           PUBLIC_HEADER
              DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
              COMPONENT Headers
   )
   install(EXPORT archon-targets
      NAMESPACE archon::
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/archon
   )
   install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
           DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
   )
   install(FILES ${CMAKE_CURRENT_BINARY_DIR}/archon-config.cmake
                 ${CMAKE_CURRENT_BINARY_DIR}/archon-config-version.cmake
                 DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/archon
   )
endif()