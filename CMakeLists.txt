# These files below are required in CMakeLists.txt otherwise errors occur requesting presence of it.
# So our three subdirectories are...

cmake_minimum_required(VERSION 3.5)

FIND_PROGRAM(APK apk)

# Add the path to any emerging (sub-)project to the list below:

if(APK)
    add_subdirectory(V2V-Protocol)
    add_subdirectory(old)
    add_subdirectory(src)
endif()
