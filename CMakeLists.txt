cmake_minimum_required(VERSION 3.31)
project(subscribe_test)

set(CMAKE_CXX_STANDARD 20)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

find_package (OpenSSL REQUIRED)
find_package(Boost 1.81.0 COMPONENTS url REQUIRED)
find_package (Threads REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spiderrock_client/Codec)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spiderrock_client/Messages)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spiderrock_client/)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(subscribe_test main.cpp)
target_link_libraries(subscribe_test PUBLIC
        ${Boost_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        Threads::Threads
)
