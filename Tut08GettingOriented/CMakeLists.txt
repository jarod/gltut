project(tut08)

file(GLOB FILES data/*)

add_executable(GimbalLock GimbalLock.cpp ${FILES})
target_link_libraries(GimbalLock ${LIBS})

add_executable(QuaternionYPR QuaternionYPR.cpp ${FILES})
target_link_libraries(QuaternionYPR ${LIBS})

add_executable(CameraRelative CameraRelative.cpp ${FILES})
target_link_libraries(CameraRelative ${LIBS})

add_executable(Interpolation Interpolation.cpp ${FILES})
target_link_libraries(Interpolation ${LIBS})
