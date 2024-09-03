# CMAKE_SYSTEM_PROCESSOR - CPU architecture name (armv7l, aarch64, x86_64)
# CMAKE_BUILD_TYPE       - Build mode (debug, profile, release)
# PSDK_VERSION           - Build psdk exact version
# PSDK_MAJOR             - Build psdk major version

cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME flutter_nfc_kit_aurora)
set(PLUGIN_NAME  flutter_nfc_kit_aurora_platform_plugin)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-psabi")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core DBus REQUIRED)
pkg_check_modules(FlutterEmbedder REQUIRED IMPORTED_TARGET flutter-embedder)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/flutter_nfc_kit_aurora_plugin.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src//help_functions.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/help_functions.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/nfcd_tag_dbus_iface.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/nfcd_ndef_dbus_iface.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/nfcd_daemon_dbus_iface.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/nfcd_tagtype2_dbus_iface.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/nfcd_tagclassic_dbus_iface.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/nfcd_adapter_dbus_iface.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/nfcd_isodep_dbus_iface.cpp   ##   
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_typifier.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_tagtype2_handler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_tagclassic_handler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_ndef_handler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_tag_handler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_adapter_handler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_daemon_handler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers/nfcd_isodep_handler.h ##
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers/nfcd_tagtype2_handler_src.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers/nfcd_tagclassic_handler_src.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers/nfcd_ndef_handler_src.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers/nfcd_tag_handler_src.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers/nfcd_adapter_handler_src.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers/nfcd_daemon_handler_src.h
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers/nfcd_isodep_handler_src.h     ##
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/nfcd_constants.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/nfcd_tagtype2_handler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/nfcd_tagclassic_handler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/nfcd_ndef_handler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/nfcd_tag_handler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/nfcd_adapter_handler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/nfcd_daemon_handler.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/nfcd_isodep_handler.cpp)   ##

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include
             ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
             ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/headers
             ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus
             ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/src/dbus/dbus_ifaces/headers
             ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers/handlers_headers
             ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/nfcd_handlers)

add_library(${PLUGIN_NAME} SHARED ${SOURCES})

set_target_properties(${PLUGIN_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden AUTOMOC ON)
target_link_libraries(${PLUGIN_NAME} PRIVATE PkgConfig::FlutterEmbedder)
target_link_libraries(${PLUGIN_NAME} PUBLIC Qt5::Core Qt5::DBus)

target_include_directories(${PLUGIN_NAME} PUBLIC ${INCLUDES})
target_compile_definitions(${PLUGIN_NAME} PRIVATE PLUGIN_IMPL)
