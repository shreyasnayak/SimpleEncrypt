cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(SimpleEncrypt VERSION 1.0.1 DESCRIPTION "SimpleEncrypt is the lib to encrypt the data")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    include_directories("/usr/include/openssl")
    link_directories("/usr/lib/")
else (WIN32)
    include_directories("/usr/include/openssl")
    link_directories("/usr/lib/")
endif (WIN32)

add_library(SimpleEncrypt SHARED
    main.cpp
    src/base64.h
    src/base64.cpp
)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
