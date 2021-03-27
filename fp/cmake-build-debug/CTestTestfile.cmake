# CMake generated Testfile for 
# Source directory: D:/cs211/fp
# Build directory: D:/cs211/fp/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test_model_test "model_test")
set_tests_properties(Test_model_test PROPERTIES  _BACKTRACE_TRIPLES "D:/cs211/fp/.cs211/cmake/211commands.cmake;47;add_test;D:/cs211/fp/CMakeLists.txt;18;add_test_program;D:/cs211/fp/CMakeLists.txt;0;")
subdirs(".cs211/lib/catch")
subdirs(".cs211/lib/ge211")
