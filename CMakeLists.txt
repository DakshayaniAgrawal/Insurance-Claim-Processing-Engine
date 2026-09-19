cmake_minimum_required(VERSION 3.15)

project(InsuranceClaimProcessingEngine
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(insurance_core
    src/Claim.cpp
    src/Policy.cpp
    src/SettlementEngine.cpp
    src/ClaimQueue.cpp
)

target_include_directories(insurance_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

if (MSVC)
    target_compile_options(insurance_core PRIVATE /W4)
else()
    target_compile_options(insurance_core PRIVATE -Wall -Wextra -pedantic)
endif()

add_executable(insurance_engine
    src/main.cpp
)

target_link_libraries(insurance_engine
    PRIVATE insurance_core
)

add_executable(test_engine
    tests/test_engine.cpp
)

target_link_libraries(test_engine
    PRIVATE insurance_core
)

enable_testing()
add_test(NAME SettlementEngineTests COMMAND test_engine)
