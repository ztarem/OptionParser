cmake_minimum_required(VERSION 3.16)
project(OptionParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(PROJECT_VERSION 1.0)

enable_testing()

add_library(OptionParser SHARED optionparserbase.cxx optionparserbase.h)
set_property(TARGET OptionParser PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET OptionParser PROPERTY SOVERSION 1)
set_property(TARGET OptionParser PROPERTY INTERFACE_OptionParser_MAJOR_VERSION 1)
set_property(TARGET OptionParser APPEND PROPERTY COMPATIBLE_INTERFACE_STRING OptionParser_MAJOR_VERSION)

install(TARGETS OptionParser EXPORT OptionParserTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )
install(FILES optionparserbase.h DESTINATION include COMPONENT Devel)
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/OptionParser/OptionParserConfigVersion.cmake"
        VERSION ${PROJECT_VERSION} COMPATIBILITY AnyNewerVersion)

export(EXPORT OptionParserTargets FILE "${CMAKE_CURRENT_BINARY_DIR}/OptionParser/OptionParserTargets.cmake"
        NAMESPACE OptionParser::)
configure_file(cmake/OptionParserConfig.cmake "${CMAKE_CURRENT_BINARY_DIR}/OptionParser/OptionParserConfig.cmake" COPYONLY)

set(ConfigPackageLocation lib/cmake/OptionParser)
install(EXPORT OptionParserTargets FILE OptionParserTargets.cmake NAMESPACE OptionParser:: DESTINATION ${ConfigPackageLocation})
install(FILES cmake/OptionParserConfig.cmake "${CMAKE_CURRENT_BINARY_DIR}/OptionParser/OptionParserConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation} COMPONENT Devel)

add_subdirectory(tests)
