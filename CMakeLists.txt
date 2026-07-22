cmake_minimum_required(VERSION 3.15)

project(QSecureLib VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Avoid RPATH install issues
set(CMAKE_SKIP_INSTALL_RPATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# -----------------------------
# Dependencies
# -----------------------------

find_package(OpenSSL REQUIRED)

if(CMAKE_CROSSCOMPILING)
    list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/arm-install")
else()
    list(APPEND CMAKE_PREFIX_PATH "/usr/local")
endif()

find_package(liboqs CONFIG REQUIRED)

option(BUILD_GUI "Build Qt GUI" ON)

if(BUILD_GUI)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    qt_standard_project_setup()
endif()

# -----------------------------
# Library
# -----------------------------

add_library(
    qsecure
    STATIC
    src/filehandler.cpp
    src/symmetric.cpp
    src/qsecure.cpp
    src/aes_gcm.cpp
    src/keymanager.cpp
    src/asymmetric.cpp
    src/hybrid.cpp
    src/container.cpp
    src/signature.cpp
)

target_include_directories(
    qsecure
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    qsecure
    PUBLIC
        oqs
        argon2
        OpenSSL::Crypto
        OpenSSL::SSL
)

# -----------------------------
# Test Programs
# -----------------------------

add_executable(
    encrypt_test
    examples/encrypt_test.cpp
)

target_link_libraries(
    encrypt_test
    PRIVATE
    qsecure
)

add_executable(
    mlkem_test
    examples/mlkem_test.cpp
)

target_link_libraries(
    mlkem_test
    PRIVATE
    qsecure
)

add_executable(
    hybrid_test
    examples/hybrid_test.cpp
)

target_link_libraries(
    hybrid_test
    PRIVATE
    qsecure
)

add_executable(
    signature_test
    examples/signature_test.cpp
)

target_link_libraries(
    signature_test
    PRIVATE
    qsecure
)

add_executable(
    key_test
    examples/key_test.cpp
)

target_link_libraries(
    key_test
    PRIVATE
    qsecure
)

add_executable(
    container_test
    examples/container_test.cpp
)

target_link_libraries(
    container_test
    PRIVATE
    qsecure
)

add_executable(
    file_signature_test
    examples/file_signature_test.cpp
)

target_link_libraries(
    file_signature_test
    PRIVATE
    qsecure
)

add_executable(
    key_protect_test
    examples/key_protect_test.cpp
)

target_link_libraries(
    key_protect_test
    PRIVATE
    qsecure
)

add_executable(
    benchmark
    examples/benchmark.cpp
)

target_link_libraries(
    benchmark
    PRIVATE
    qsecure
)

# -----------------------------
# Qt GUI
# -----------------------------

if(BUILD_GUI)

qt_add_executable(
    qsecure_gui
    gui/main.cpp
    gui/mainwindow.cpp
    gui/mainwindow.h
)

target_link_libraries(
    qsecure_gui
    PRIVATE
        Qt6::Widgets
        qsecure
)

install(
    TARGETS qsecure_gui
    RUNTIME DESTINATION bin
)

endif()

# -----------------------------
# Install Rules
# -----------------------------

install(
    TARGETS qsecure
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include/qsecure
)



# -----------------------------
# CPack / DEB Packaging
# -----------------------------

set(CPACK_PACKAGE_NAME "QSecure")
set(CPACK_PACKAGE_VENDOR "Kishan")
set(CPACK_PACKAGE_CONTACT "kishan@example.com")

set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Post-Quantum File Encryption and Digital Signature Suite"
)

set(CPACK_GENERATOR "DEB")

# Package into /usr instead of /usr/local
set(CPACK_SET_DESTDIR ON)
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

# Debian metadata
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kishan")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

set(
    CPACK_DEBIAN_PACKAGE_DEPENDS
    "libssl3, libqt6widgets6"
)

include(CPack)
