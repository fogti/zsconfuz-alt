cmake_minimum_required(VERSION 3.7)
project(zsconfuz-alt LANGUAGES C)

set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for binaries")
set(INSTALL_LIBEXEC_DIR libexec/zsconfuz-alt CACHE PATH "Installation directory for helper binaries")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-plt -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables")

add_executable(zscfz-ppsec  src/ppsec.c)
add_executable(zscfz-runcmd src/runcmd.c)

install(TARGETS zscfz-ppsec zscfz-runcmd DESTINATION "${INSTALL_LIBEXEC_DIR}")
install(PROGRAMS zscfz2ninja.sh DESTINATION "${INSTALL_LIBEXEC_DIR}")
install(PROGRAMS zsconfuz-alt DESTINATION "${INSTALL_BIN_DIR}")
