cmake_minimum_required(VERSION 3.0.2)

project(ErrorRate CXX)

option(EXE_TESTING "Включить модульное тестирование" ON)

if (EXE_TESTING)
    find_package(GTest REQUIRED)
endif()

add_executable(${PROJECT_NAME} main.cpp)
add_library(errorRateLib errorRate.cpp)
target_link_libraries(${PROJECT_NAME} errorRateLib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(errorRateLib PRIVATE
        /W4
    )
else ()
    target_compile_options(${PROJECT_NAME}  PRIVATE
        -Wall -Wextra -pedantic -g3 -Wpointer-arith -Werror -pedantic-errors
    )
    target_compile_options(errorRateLib  PRIVATE
        -Wall -Wextra -pedantic -g3 -Wpointer-arith -Werror -pedantic-errors
    )
endif()


if(NOT EXE_TESTING)
    message(STATUS "Тестирование проекта ${PROJECT_NAME} выключено")
elseif(IS_SUBPROJECT)
    message(STATUS "${PROJECT_NAME} не тестируется в режиме подмодуля")
else()
    add_subdirectory(unit_test)
endif()

