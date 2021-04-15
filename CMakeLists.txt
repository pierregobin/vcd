cmake_minimum_required(VERSION 3.10)

include(./src/CMakeLists.txt libvcd)

project(dumpvar)

include_directories(./src)

add_executable(${CMAKE_PROJECT_NAME}
    test/${CMAKE_PROJECT_NAME}.c 
)

target_link_libraries(${CMAKE_PROJECT_NAME} vcd)


project(dumpvarint)

include_directories(./src)

add_executable(${CMAKE_PROJECT_NAME}
    test/${CMAKE_PROJECT_NAME}.c 
)

target_link_libraries(${CMAKE_PROJECT_NAME} vcd)

project(var)

include_directories(./src)

add_executable(${CMAKE_PROJECT_NAME}
    test/${CMAKE_PROJECT_NAME}.c 
)

target_link_libraries(${CMAKE_PROJECT_NAME} vcd)

project(date)

include_directories(./src)

add_executable(${CMAKE_PROJECT_NAME}
    test/${CMAKE_PROJECT_NAME}.c 
)

target_link_libraries(${CMAKE_PROJECT_NAME} vcd)

project(openclose)

include_directories(./src)

add_executable(${CMAKE_PROJECT_NAME}
    test/${CMAKE_PROJECT_NAME}.c 
)

target_link_libraries(${CMAKE_PROJECT_NAME} vcd)

project(comment)

include_directories(./src)

add_executable(${CMAKE_PROJECT_NAME}
    test/${CMAKE_PROJECT_NAME}.c 
)

target_link_libraries(${CMAKE_PROJECT_NAME} vcd)