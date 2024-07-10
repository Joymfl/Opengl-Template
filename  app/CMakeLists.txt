add_executable(3dTester main.c
        stb_image.h)

target_link_libraries(3dTester PUBLIC shaderHelpers)
target_link_libraries(3dTester PUBLIC openglHelper)
