if(USE_EXP)
  include_directories(../../exp/apps/bfs .)
endif()
app(bfs-approx_sel_push_extreme2 bfs.cpp)
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "XL")
  app(diameter-approx_sel_push_extreme2 Diameter.cpp)
endif()
