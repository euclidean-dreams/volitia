cmake_minimum_required(VERSION 3.16)
project(volitia)

set(CMAKE_CXX_STANDARD 14)

include(lib/cmake-utils/dependency-integrator.cmake)
integrate_cmake_dependency(
        NAME pigpio
        GIT_URL git@github.com:joan2937/pigpio.git
        GIT_TAG c33738a320a3e28824af7807edafda440952c05d
)
integrate_cmake_dependency(
        NAME impresario-utils
        GIT_URL git@github.com:impresario-systems/impresario-utils.git
        GIT_TAG origin/dev
)

set(
        SOURCE_FILES
        src/Config.h
        src/SpiBanger.cpp src/SpiBanger.h
        src/HomunculusWrangler.cpp src/HomunculusWrangler.h

        src/bonds/Pollable.h
        src/bonds/CalypsoBond.cpp src/bonds/CalypsoBond.h
        src/bonds/GeminiBond.cpp src/bonds/GeminiBond.h

        src/ParcelMaster.cpp src/ParcelMaster.h
)
list(APPEND TARGETS volitia)
add_executable(volitia src/main.cpp ${SOURCE_FILES})

# finalize
foreach (target IN LISTS TARGETS)
    target_include_directories(${target} PRIVATE src)
    target_include_directories(${target} PRIVATE ${CMAKE_BINARY_DIR}/pigpio-src)
    target_link_libraries(${target} PRIVATE pigpio)
    target_link_libraries(${target} PRIVATE pthread)
    target_link_libraries(${target} PRIVATE impresario-utils)
    target_link_libraries(${target} PRIVATE zmq)
    target_link_libraries(${target} PRIVATE yaml-cpp)
endforeach ()
