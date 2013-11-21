project(tut05)

file(GLOB FILES data/*)

add_executable(OverlapNoDepth OverlapNoDepth.cpp ${FILES})
target_link_libraries(OverlapNoDepth ${LIBS})

add_executable(BaseVertexOverlap BaseVertexOverlap.cpp ${FILES})
target_link_libraries(BaseVertexOverlap ${LIBS})

add_executable(DepthBuffer DepthBuffer.cpp ${FILES})
target_link_libraries(DepthBuffer ${LIBS})

add_executable(VertexClipping VertexClipping.cpp ${FILES})
target_link_libraries(VertexClipping ${LIBS})

add_executable(DepthClamping DepthClamping.cpp ${FILES})
target_link_libraries(DepthClamping ${LIBS})

add_executable(DepthFighting DepthFighting.cpp ${FILES})
target_link_libraries(DepthFighting ${LIBS})
