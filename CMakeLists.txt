cmake_minimum_required(VERSION 3.7)
project(zsconfuz-alt)

set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for binaries")
set(INSTALL_LIBEXEC_DIR libexec/zsconfuz-alt CACHE PATH "Installation directory for helper binaries")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-plt -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-plt -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables")

add_executable(zscfz-ecatch src/ecatch.c)
add_executable(zscfz-ppsec src/ppsec.cxx)

install(TARGETS zscfz-ecatch zscfz-ppsec DESTINATION "${INSTALL_LIBEXEC_DIR}")
install(PROGRAMS zscfz2ninja.sh zscfz-runcmd DESTINATION "${INSTALL_LIBEXEC_DIR}")
install(PROGRAMS zsconfuz-alt DESTINATION "${INSTALL_BIN_DIR}")
