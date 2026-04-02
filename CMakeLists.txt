cmake_minimum_required(VERSION 4.0)
project(cooperate_alg)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithms-and-data-structures main.cpp
        timkoffy/helper.h
        timkoffy/data_structures/stack.h
        timkoffy/data_structures/queue.h
        timkoffy/data_structures/graph_adjlist.h
        timkoffy/tasks/fib.h
        timkoffy/tasks/rle.h
        timkoffy/tasks/calc_dextra.h
        timkoffy/data_structures/graph_adjmatrix.h
        timkoffy/data_structures/linked_list.h
        timkoffy/data_structures/hashmap.h
        timkoffy/tasks/calc_dextra.h
        timkoffy/data_structures/array.h
        timkoffy/tasks/euler_path.h
        timkoffy/data_structures/bloom_filter.h
        timkoffy/tasks/count_substrings_with_hashmap.h
        timkoffy/tasks/find_cycle_graph.h
        timkoffy/tasks/render_graph.h
        timkoffy/tasks/negative_pow.h
        timkoffy/tasks/print_unique_chars.h)
