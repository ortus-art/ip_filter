cmake_minimum_required(VERSION 3.2)

set(PROJECT_LIB ${PROJECT_NAME}_lib)

set(ip_filter_lib_src
    parse_exception.h
    ip_filter.h
    ip_filter.cpp
)

#Create a static library that is shared between main application and tests
add_library(${PROJECT_LIB} STATIC ${ip_filter_lib_src})
target_include_directories(${PROJECT_LIB} PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
