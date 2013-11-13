project(tut02)

add_executable(FragPosition FragPosition.cpp ../framework/framework.cpp)
target_link_libraries(FragPosition ${LIBS})

add_executable(VertexColors VertexColors.cpp ../framework/framework.cpp)
target_link_libraries(VertexColors ${LIBS})