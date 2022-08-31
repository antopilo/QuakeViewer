add_subdirectory(Dependencies/NuakeRenderer)

set(HEADERS QuakeViewer/Camera.h  QuakeViewer/Renderer.h QuakeViewer/Input.h QuakeViewer/FileSystem.h 
QuakeViewer/Vertex.h QuakeViewer/Mesh.h)
set(SOURCES main.cpp QuakeViewer/Camera.cpp QuakeViewer/Renderer.cpp QuakeViewer/Input.cpp 
QuakeViewer/Mesh.cpp)

add_executable(QuakeViewer ${HEADERS} ${SOURCES})
set_property(TARGET QuakeViewer PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS} ${SOURCES})

target_link_libraries(QuakeViewer PUBLIC NuakeRenderer)
target_include_directories(QuakeViewer PUBLIC ./Dependencies/NuakeRenderer/ ./Vendors/)