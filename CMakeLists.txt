cmake_minimum_required(VERSION 3.10)

# set the project name
project(CollegePractices)

# add the executable
add_executable(CollegePractices Source/main.cpp Source/wrapper/wrapper.hpp Source/wrapper/win/win_wrapper.hpp Source/wrapper/posix/posixwrapper.cpp Source/wrapper/posix/posixwrapper.hpp Source/wrapper/file/file_wrapper.cpp Source/wrapper/file/file_wrapper.hpp Source/wrapper/string/wrappedstring.cpp Source/wrapper/string/wrappedstring.hpp)

