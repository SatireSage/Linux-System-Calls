# Linux Syscalls

Authors: [Sahaj Singh](https://github.com/SatireSage)

This repository contains the code for two system calls implemented in the Linux kernel: Array Statistics Syscall and Process Ancestors Syscall. Both syscalls are designed to help you become familiar with accessing memory between user and kernel space.

## Getting Started

Clone this repository to your local machine using the following command:

<pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span></span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg></button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-bash">git clone https://github.com/yourusername/Array-Statistics-and-Process-Ancestors-Syscall.git
</code></div></div></pre>

## Directory Structure

<pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span></span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg></button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-markdown">.
├── cmpt300
│   ├── array_stats.c
│   ├── array_stats.h
│   ├── process_ancestors.c
│   └── process_ancestors.h
└── tests
    ├── array_stats_test.c
    └── process_ancestors_test.c
</code></div></div></pre>

## Syscalls

### 1. Array Statistics Syscall

This syscall computes basic statistics (max, min, sum) on an array of data.

**System Call Number** : 437

**Signature** : `asmlinkage long sys_array_stats(struct array_stats *stats, long *data, long size);`

#### Files:

- cmpt300/array_stats.h
- cmpt300/array_stats.c
- tests/array_stats_test.c

### 2. Process Ancestors Syscall

This syscall returns information about the current process and its ancestors (parent process, grandparent process, etc.).

**System Call Number** : 438

**Signature** : `asmlinkage long sys_process_ancestors(struct process_info *info_array, long size, long *num_filled);`

#### Files:

- cmpt300/process_ancestors.h
- cmpt300/process_ancestors.c
- tests/process_ancestors_test.c

## Testing

The `tests` directory contains test files for both syscalls. To test the syscalls, compile and run each test file:

<pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span></span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg></button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-bash">gcc -o array_stats_test array_stats_test.c
./array_stats_test

gcc -o process_ancestors_test process_ancestors_test.c
./process_ancestors_test
</code></div></div></pre>

## License

This project is licensed under the MIT License.

## Acknowledgments

- Assignment instructions and base code provided by the course instructor for CMPT 300, Steven Ko.
