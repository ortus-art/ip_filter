cmake_minimum_required(VERSION 3.2)

include(CodeCoverage)
setup_target_for_coverage(${PROJECT_NAME}_coverage 
  ${PROJECT_NAME}_test 
  coverage
  ${CMAKE_CURRENT_SOURCE_DIR} )

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

set(PROJETC_TEST ${PROJECT_NAME}_test)

add_executable(${PROJETC_TEST} test.cpp)


set_target_properties(${PROJETC_TEST} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(${PROJETC_TEST} PROPERTIES
  APPEND PROPERTY COMPILE_DEFINITIONS PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)


target_include_directories(${PROJETC_TEST} PUBLIC
  ${GTEST_INCLUDE_DIRS}
  ${OPENSSL_INCLUDE_DIR}
)
target_include_directories(${PROJETC_TEST} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/src
)

target_link_libraries(${PROJETC_TEST}
    Threads::Threads
    OpenSSL::SSL)

target_link_libraries(${PROJETC_TEST} 
  ${PROJECT_NAME}_lib 
  ${GTEST_BOTH_LIBRARIES}
)



add_test(main_case ${PROJETC_TEST})
