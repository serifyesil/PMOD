if(USE_EXP)
  include_directories(../../exp/apps/bfs .)
endif()
app(bfs bfs.cpp)
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "XL")
  app(diameter Diameter.cpp)
endif()
