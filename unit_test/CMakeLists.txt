message ("Добавлены модульные тесты")
add_executable(test_errorRate test_errorRate.cpp)

target_link_libraries(
    test_errorRate ${GTEST_LIBRARIES} gtest_main Threads::Threads errorRateLib
)

set_target_properties(test_errorRate PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(test_errorRate PRIVATE
        /W4
    )
else ()
    target_compile_options(test_errorRate PRIVATE
        -Wall -Wextra -pedantic -g3 -Wpointer-arith -Werror -pedantic-errors
    )
endif()

enable_testing()

add_test(test_errorRate test_errorRate)