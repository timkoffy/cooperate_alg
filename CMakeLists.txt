cmake_minimum_required(VERSION 4.0)
project(cooperate_alg)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithms-and-data-structures main.cpp
        timkoffy/helper.h
        timkoffy/my_stack.h
        timkoffy/my_queue.h
        timkoffy/my_graph_adjlist.h
        timkoffy/fib.h
        timkoffy/rle.h
        timkoffy/calc_dextra.h
        timkoffy/graph_adjmatrix.h
        timkoffy/linked_list.h
        timkoffy/hashmap_linkedlist.h
        timkoffy/calc_dextra.h
        timkoffy/array.h
        timkoffy/eulerPath.h)
