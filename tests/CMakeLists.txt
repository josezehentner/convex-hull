add_executable(convex_tests
        TestPoints.cpp
        TestAndrew.cpp
        TestQuickHull.cpp
        TestIntegration.cpp
)

target_link_libraries(convex_tests PRIVATE convex_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(convex_tests)
