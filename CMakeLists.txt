# CMakeList.txt : CMake project for Code_Forests, include source and define
# project specific logic here.
#


# Project name
project("Code_Forests")


# Targets
set(PROJECT ${PROJECT_NAME})
set(PROJECT_LIB ${PROJECT}_lib)
set(PROJECT_APP ${PROJECT}_app)


# Library
add_library(${PROJECT_LIB})


# Subdirectories
set(SUBDIRECTORIES src)
foreach(VAR ${SUBDIRECTORIES})
  add_subdirectory(${VAR})
endforeach()


# Setup options
set(CODEFORESTS_RESOURCE_GROUP "CodeForests" CACHE STRING "The media resource group used, e.g. 'CodeForests'.")
set(CODEFORESTS_CONFIG_PATH "${CMAKE_SOURCE_DIR}/data/config/config.txt" CACHE STRING "The absolute path to the configuration file.")
set(CODEFORESTS_MATERIALS_PATH "${CMAKE_SOURCE_DIR}/data/materials/materials.material" CACHE STRING "The absolute file path to the material file.")
set(OGRE_DIR "C:/code-forests/ogre")

# Find 3rd party packages
find_package(Boost REQUIRED)
find_package(OGRE REQUIRED COMPONENTS Bites Overlay CONFIG)
find_package(OpenGL REQUIRED)


# Compile definitions
message("CodeForests definitions:")
message("Found CODEFORESTS_RESOURCE_GROUP: " ${CODEFORESTS_RESOURCE_GROUP})
message("Found CODEFORESTS_CONFIG_PATH: " ${CODEFORESTS_CONFIG_PATH})
message("Found CODEFORESTS_MATERIALS_PATH: " ${CODEFORESTS_MATERIALS_PATH})
message(" ")

target_compile_definitions(${PROJECT_LIB} PUBLIC CODEFORESTS_RESOURCE_GROUP="${CODEFORESTS_RESOURCE_GROUP}")
target_compile_definitions(${PROJECT_LIB} PUBLIC CODEFORESTS_CONFIG_PATH="${CODEFORESTS_CONFIG_PATH}")
target_compile_definitions(${PROJECT_LIB} PUBLIC CODEFORESTS_MATERIALS_PATH="${CODEFORESTS_MATERIALS_PATH}")


# Include directories
target_include_directories(${PROJECT_LIB} PUBLIC src)


# Linking
set(BOOST_LIBRARIES ${Boost_LOG_LIBRARY} ${Boost_LOG_SETUP_LIBRARY})
set(JSONCPP_LIBRARIES libjsoncpp.so)
set(SDL2_LIBRARIES libSDL2.so)
set(THIRD_PARTY_LIBRARIES
  ${JSONCPP_LIBRARIES}
  ${OGRE_LIBRARIES}
  ${BOOST_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

target_link_libraries(${PROJECT_LIB} PUBLIC ${THIRD_PARTY_LIBRARIES})


# App
set(APP_FILES src/main.cpp)
add_executable(${PROJECT_APP} ${APP_FILES})
target_link_libraries(${PROJECT_APP} PUBLIC ${PROJECT_LIB})
