if(USE_EXP)
  include_directories(../../exp/apps/pagerank .)
endif()
app(pagerank-approx-cas PageRank.cpp)
