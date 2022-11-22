cmake_minimum_required(VERSION 3.5)

project(GeoJSONParser LANGUAGES CXX)
set(version 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GeoJSONParser_H ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GeoJSONParser_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
find_path(RapidJSON_INCLUDE_DIRS rapidjson)


set(HDRS
    ${GeoJSONParser_H}/object.h
    ${GeoJSONParser_H}/featurecollection.h
    ${GeoJSONParser_H}/feature.h
    ${GeoJSONParser_H}/geometry.h
    ${GeoJSONParser_H}/point.h
    ${GeoJSONParser_H}/multipoint.h
    ${GeoJSONParser_H}/linestring.h
    ${GeoJSONParser_H}/multilinestring.h
    ${GeoJSONParser_H}/polygon.h
    ${GeoJSONParser_H}/multipolygon.h
    ${GeoJSONParser_H}/geometrycollection.h
    ${GeoJSONParser_H}/utils.h
    ${GeoJSONParser_H}/types.h
)
set(SRCS
    ${GeoJSONParser_SRC}/featurecollection.cpp
    ${GeoJSONParser_SRC}/feature.cpp
    ${GeoJSONParser_SRC}/point.cpp
    ${GeoJSONParser_SRC}/multipoint.cpp
    ${GeoJSONParser_SRC}/linestring.cpp
    ${GeoJSONParser_SRC}/multilinestring.cpp
    ${GeoJSONParser_SRC}/polygon.cpp
    ${GeoJSONParser_SRC}/multipolygon.cpp
    ${GeoJSONParser_SRC}/geometrycollection.cpp
    ${GeoJSONParser_SRC}/utils.cpp
)

add_library(GeoJSONParser ${HDRS} ${SRCS})
target_include_directories(GeoJSONParser PUBLIC $<BUILD_INTERFACE:${GeoJSONParser_H}/> ${RapidJSON_INCLUDE_DIRS})

add_executable(GeoJSONParser_Test ${HDRS} ${SRCS} ${GeoJSONParser_SRC}/main.cpp)
target_include_directories(GeoJSONParser_Test PUBLIC $<BUILD_INTERFACE:${GeoJSONParser_H}/> ${RapidJSON_INCLUDE_DIRS})

install(FILES  ${HDRS}  DESTINATION include/GeoJSONParser-${version})
install(TARGETS GeoJSONParser
        DESTINATION lib/GeoJSONParser-${version}
        EXPORT GeoJSONParser-targets)
install(EXPORT GeoJSONParser-targets
        DESTINATION lib/GeoJSONParser-${version})

configure_file(
   ${GeoJSONParser_SOURCE_DIR}/pkg/geojsonparser-config.cmake.in
   ${GeoJSONParser_BINARY_DIR}/pkg/geojsonparser-config.cmake @ONLY)

configure_file(
   ${GeoJSONParser_SOURCE_DIR}/pkg/geojsonparser-config-version.cmake.in
   ${GeoJSONParser_BINARY_DIR}/pkg/geojsonparser-config-version.cmake @ONLY)

install(FILES ${GeoJSONParser_BINARY_DIR}/pkg/geojsonparser-config.cmake
         ${GeoJSONParser_BINARY_DIR}/pkg/geojsonparser-config-version.cmake
         DESTINATION lib/GeoJSONParser-${version})

