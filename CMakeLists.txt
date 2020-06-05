cmake_minimum_required(VERSION 3.15.3)
project(MotifDiscovery)

set(CMAKE_CXX_STANDARD 14)

add_executable(MotifDiscovery main.cpp Problem.cpp Problem.h Greedy.cpp Greedy.h ConsensusString.cpp ConsensusString.h GRASP.cpp GRASP.h LocalSearch.cpp LocalSearch.h Perturbation.cpp Perturbation.h Solution.cpp Solution.h)