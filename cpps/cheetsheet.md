## General
1. Lib - `<omp.h>`

2. func/direc. - 
    
    `#pragma omp parallel for{}`.

    `#pragma omp parallel for reduction(+:sum){}`

    `omp_get_thread_num()`

    `omp_get_num_threads()`

3. Aggregations -> reduction

    `reduction(+:sum)`
    
    `reduction(*:product)`
    
    `reduction(max:max_val)`
    
    `reduction(min:min_val)`

4. Execution Rule -> `g++ file.cpp -fopenmp -o file && ./file`

## Problem Specifics
1. BFS - 

        current_level = [0]
        Loop:
            next_level = []
            For each node in current_level (PARALLEL):
                explore neighbors
                add new nodes to next_level
            current_level = next_level