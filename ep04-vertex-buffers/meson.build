project('ep04-vertex-buffers', 'cpp')

gl = dependency('gl')
glfw3 = dependency('glfw3')
glew = dependency('glew')

deps = [gl, glfw3, glew]
incdir = include_directories('include')
sources = ['src/main.cpp']

executable('app', sources, include_directories: incdir, dependencies: deps)
