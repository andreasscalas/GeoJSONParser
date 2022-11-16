cmake_minimum_required(VERSION 3.5)

project(GeoJSONParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GeoJSON_H ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(GeoJSON_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
find_package(RapidJSON)
find_path(RAPIDJSON_H rapidjson-master/include/)
include_directories(GeoJSONParser
    ${RAPIDJSON_H}
)
set(HDRS
    ${GeoJSON_H}/object.h
    ${GeoJSON_H}/featurecollection.h
    ${GeoJSON_H}/feature.h
    ${GeoJSON_H}/geometry.h
    ${GeoJSON_H}/point.h
    ${GeoJSON_H}/multipoint.h
    ${GeoJSON_H}/linestring.h
    ${GeoJSON_H}/multilinestring.h
    ${GeoJSON_H}/polygon.h
    ${GeoJSON_H}/multipolygon.h
    ${GeoJSON_H}/geometrycollection.h
    ${GeoJSON_H}/utils.h
    ${GeoJSON_H}/types.h
)
set(SRCS
    ${GeoJSON_SRC}/featurecollection.cpp
    ${GeoJSON_SRC}/feature.cpp
    ${GeoJSON_SRC}/point.cpp
    ${GeoJSON_SRC}/multipoint.cpp
    ${GeoJSON_SRC}/linestring.cpp
    ${GeoJSON_SRC}/multilinestring.cpp
    ${GeoJSON_SRC}/polygon.cpp
    ${GeoJSON_SRC}/multipolygon.cpp
    ${GeoJSON_SRC}/geometrycollection.cpp
    ${GeoJSON_SRC}/utils.cpp
)

add_library(GeoJSONParser ${HDRS} ${SRCS})
target_include_directories(GeoJSONParser PUBLIC ${GeoJSON_H} ${RAPIDJSON_H})

add_executable(GeoJSONParser_Test ${HDRS} ${SRCS} ${GeoJSON_SRC}/main.cpp)
target_include_directories(GeoJSONParser_Test PUBLIC ${GeoJSON_H} ${RAPIDJSON_H})
