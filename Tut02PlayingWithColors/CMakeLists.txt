project(tut02)

file(GLOB FILES data/*)

add_executable(FragPosition FragPosition.cpp ${FILES})
target_link_libraries(FragPosition ${LIBS})

add_executable(VertexColors VertexColors.cpp ${FILES})
target_link_libraries(VertexColors ${LIBS})
