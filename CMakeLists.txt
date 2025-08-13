cmake_minimum_required(VERSION 3.28)
project(subscribe_test)

set(CMAKE_CXX_STANDARD 20)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

find_package (OpenSSL REQUIRED)
find_package (Boost 1.81.0 COMPONENTS url REQUIRED)
find_package (Protobuf REQUIRED)
find_package (Threads REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Codec)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Messages)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(live_prints MLinkStreamHandler.cpp live_data.cpp)
target_link_libraries(live_prints PUBLIC
        ${Boost_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${PROTO_BASE}
        Threads::Threads
)

add_executable(historic_prints historic_data.cpp)

add_executable(file_compare file_compare.cpp)
