cmake_minimum_required(VERSION 3.2)

project(dit168)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

find_package(libcluon REQUIRED)
include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})


add_executable(${PROJECT_NAME}.Sender ${CMAKE_CURRENT_SOURCE_DIR}/sender.cpp ${CMAKE_CURRENT_SOURCE_DIR}/oddEvenChecker.cpp)

target_link_libraries(${PROJECT_NAME}.Sender ${CLUON_LIBRARIES})

add_executable(${PROJECT_NAME}.Receiver ${CMAKE_CURRENT_SOURCE_DIR}/receiver.cpp ${CMAKE_CURRENT_SOURCE_DIR}/oddEvenChecker.cpp)

target_link_libraries(${PROJECT_NAME}.Receiver ${CLUON_LIBRARIES})
