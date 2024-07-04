add_executable(3dTester main.c)

target_link_libraries(3dTester PUBLIC shaderHelpers)
target_link_libraries(3dTester PUBLIC openglHelper)
