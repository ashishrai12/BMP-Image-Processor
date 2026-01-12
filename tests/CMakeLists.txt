add_executable(test_basic test_basic.c)
target_include_directories(test_basic PRIVATE ../include)
target_sources(test_basic PRIVATE ../src/bmp_utils.c)
add_test(NAME BasicTest COMMAND test_basic)
