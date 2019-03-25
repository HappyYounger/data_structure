cmake_minimum_required(VERSION 3.12)
project(data_structure C)

set(CMAKE_C_STANDARD 99)

add_executable(data_structure main.c global.h global.c pool/pool.h pool/pool.c adt/adt.h list/list.c list/list.h list/linked_list.c list/linked_list.h adt/adt.c)