// Test application for the process_ancestors syscall.
#include "process_ancestors.h"
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>

#define PROCESS_ANCESTORS_SYSCALL_NUM 438
#define ARRAY_SIZE 100

long process_ancestors_syscall(struct process_info *stats, long size, long *num_filled)
{
    return syscall(PROCESS_ANCESTORS_SYSCALL_NUM, stats, size, num_filled);
}

void test_successful_case()
{
    struct process_info stats[ARRAY_SIZE];
    long num_filled;
    errno = 0;
    long result = process_ancestors_syscall(stats, ARRAY_SIZE, &num_filled);
    assert(result == 0);
    assert(num_filled > 0);
    printf("Test successful case: PASSED\n");
}

void test_larger_size()
{
    struct process_info stats[ARRAY_SIZE];
    long num_filled = 0;
    errno = 0;
    long result = process_ancestors_syscall(stats, ARRAY_SIZE + 10, &num_filled);
    assert(result == 0);
    assert(num_filled > 0 && num_filled <= ARRAY_SIZE + 10);
    printf("Test larger size: PASSED\n");
}

void test_smaller_size()
{
    struct process_info stats[ARRAY_SIZE];
    long num_filled = 0;
    errno = 0;
    long result = process_ancestors_syscall(stats, ARRAY_SIZE - 10, &num_filled);
    assert(result == 0);
    assert(num_filled > 0 && num_filled <= ARRAY_SIZE - 10);
    printf("Test smaller size: PASSED\n");
}

void test_negative_size()
{
    struct process_info stats[ARRAY_SIZE];
    long num_filled = 0;
    errno = 0;
    long result = process_ancestors_syscall(stats, -1, &num_filled);
    assert(result == -1 && errno == EINVAL);
    printf("Test negative size: PASSED\n");
}

void test_null_stats_pointer()
{
    long num_filled = 0;
    errno = 0;
    long result = process_ancestors_syscall(NULL, ARRAY_SIZE, &num_filled);
    assert(result == -1 && errno == EFAULT);
    printf("Test null stats pointer: PASSED\n");
}

void test_null_num_filled_pointer()
{
    struct process_info stats[ARRAY_SIZE];
    errno = 0;
    long result = process_ancestors_syscall(stats, ARRAY_SIZE, NULL);
    assert(result == -1 && errno == EFAULT);
    printf("Test null num_filled pointer: PASSED\n");
}

void retrieve_process_ancestor_info(int expected_num_filled)
{
    struct process_info stats[ARRAY_SIZE];
    long num_filled = 0;
    long result = process_ancestors_syscall(stats, ARRAY_SIZE, &num_filled);

    if (result == 0)
    {
        if (expected_num_filled >= 0)
            assert(num_filled >= expected_num_filled);
    }
    else
    {
        printf("Error occurred while retrieving process ancestor information.\n");
        printf("Error code: %ld\n", result);
        assert(0);
    }
}

void test_children(int depth)
{
    pid_t pids[depth];
    for (int i = 0; i < depth; i++)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            retrieve_process_ancestor_info(i);
            exit(0);
        }
        else if (pids[i] < 0)
        {
            perror("Error in fork()");
            exit(1);
        }
    }
    for (int i = 0; i < depth; i++)
        wait(NULL);
    retrieve_process_ancestor_info(-1);
    printf("Test with %d children: PASSED\n", depth);
}

int main()
{
    // Test cases:
    test_successful_case();
    test_larger_size();
    test_smaller_size();
    test_negative_size();
    test_null_stats_pointer();
    test_null_num_filled_pointer();
    test_children(5);

    return 0;
}