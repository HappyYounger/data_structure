cmake_minimum_required(VERSION 3.12)
project(data_structure C)

set(CMAKE_C_STANDARD 99)

add_executable(data_structure main.c global.h global.c pool/pool.h pool/pool.c adt/adt.h list/list.c list/list.h list/linked_list.c list/linked_list.h adt/adt.c stack/stack.c stack/stack.h stack/linked_stack.c stack/linked_stack.h stack/sample/expression.c stack/sample/expression.h queue/queue.c queue/queue.h queue/circle_queue.c queue/circle_queue.h tree/tree.c tree/tree.h tree/binary_tree.c tree/binary_tree.h graph/graph.c graph/graph.h graph/directed_graph.c graph/directed_graph.h)