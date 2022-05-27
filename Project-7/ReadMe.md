# Project: Multi-Threading
## Overview
Use threads to create concurrenlty executable code.
### Objectives
- Learn how to write a multi-threaded program
- Learn how to build multi-thread safe data structures
## Description
### Introduction
Modern computer programming makes extensive use of concurrent execution through the use of threads.
Multi-threaded programming, requires careful management of data structures to make them multi-thread safe.

Investigate thread-safe coding by building three simple utility libraries.
The first is a simple counter that multiple threads can use.
The second is a hash table, an important data structure used in many multi-threaded applications as well as in the operating system itself.
Finally, the third is a data structure that maintains a set of the most recently used (MRU) objects.
### What to do
- Multi-Threaded Counter
   *  Implement thread-safe increment, decrement, and get value procedures.
   *  The header file for this library is provided as MTCounter.h
- Multi-Threaded Hash Table
   * Implement a thread-safe hash table that will only store integers.
   * The header file for this library is provided as MTHash.h
- Multi-Threaded Cache
   * Implement a data structure to track a set of positive integers that retains the Most Recently Used (MRU) entries.
   * When the cache is full, space should be made for new entires by removing the Least Recently Used (LRU) data.
   * The header file for this library is provided as MTCache.h
