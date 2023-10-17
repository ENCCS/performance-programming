Architecture
------------


.. 
   A crash course in computer architecture
        This part gives an overview of computer architecture including common implementation
        techniques and how to adapt code to get the best performance from them.

        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        A computer is a device that executes a *machine code program*, with each major family
        of processors having its own *machine language* or *architecture*. A machine code
        program is a sequence of *instructions*, which are executed one at a time and by
        default in the order they occur in the program. 

        Every architecture includes
        instructions that redirects execution to a different part of the program rather than
        the next instruction, thus changing the flow of control. Some instructions, called
        *conditional branches* evaluate a (data dependent) condition, jumping to another
        part of the program if the condition is satisfied, otherwise proceeding to the
        following instruction. These correspond to, and are used to implement, control flow
        statements like **if**, **for**, and **while** in high level languages.

        Other common kinds of instruction include arithmetic on integers and floating point
        numbers of different sizes, logical operations such as **and**, **or**, and **xor**.
        There are typically also instructions for moving data around.

        Instructions work with data stored in *memory*, *registers*, or included in the
        instruction itself. Most of the data used by a program is stored in the main memory
        which contains up to many billions of data items and is similar to a large array.
        Each location in memory has its own unique *address* and is read or written to 
        by memory referencing instructions using this address.

        Each register contains a single item of data. In current architectures, registers are
        either 32 or 64 bits in size, so a register can hold a single integer och floading
        point number. In most architectures, the register set is divided into general purpose
        registers containing integers (including memory addresses) or similar data, and 
        floating point registers. Since the introduction of MMX in 1997, there has also been
        registers containing vectors of scalar data elements. These *SIMD* registers are
        typically larger still, with sizes up to 512 bits.

        Memory hierarchies
        ^^^^^^^^^^^^^^^^^^

        It is a truth universally acknowledged, that a computer memory is either large or
        fast. It is also the case that many programs tend to access memory locations that
        they have accessed in the recent past, or memory locations near them. This property
        is called *locality*, either *temporary locality* (same locations) or
        *spatial locality* (nearby locations).

        Locality makes it possible to improve performance by combining a larger, slower,
        memory with a smaller, faster one. We have already seen this concept in the use of
        a few dozen processor registers, together with a main memory containing billions
        of individual locations. But modern machines often have several layers of
        progressively larger and slower memory between the registers and the true main 
        memory. All of the layers together are referred to as the *memory hierarchy* of the
        machine.

        This raises the issue of keeping track of which value is in what memory. When it
        comes to registers, that is typically the job of the compiler. A C or Fortran
        program does not specify which registers should be used for which variables but
        register use is explicit in the machine code.

        For larger memories it is typically either the programmer or the processor hardware
        itself that makes the decision. For instance, when programming a GPU in Cuda, the
        programmer specifies the kind of memory each variable should use. Such memories
        that are visible to the programmer are often called *local memories* or
        *scratchpad memories*. If the memory is managed by the hardware, it is called
        a *cache*.

        For general purpose processors, such as the x86 processors that are found in
        everything from laptops to supercomputers, the memory hierarchy below the processor
        registers is managed by the hardware. The strategy is based on the principle of
        locality discussed above; when a memory location is accessed, its contents is copied
        to the highest level in the memory hierarchy (if it is not already there) so that it
        will be readily available if it is used again soon (temporal locality). In practice,
        a small block of memory containing the interesting
        location is copied, both to amortize the cost of keeping track of memory locations
        over somewhat larger blocks, and to exploit spatial locality. Such blocks are
        called *cache lines*; today a common size is 64 bytes.

        On a machine with caches, a memory reference first checks the highest level (*L1*)
        cache. If the location in question is present in the L1 cache, the memory reference
        is an (L1) hit and is satisfied by the cache. Otherwise it is an (L1) *miss* and
        the next level in the memory hierarchy is consulted. Note that the L1 cache is the
        smallest and fastest cache; the next level is bigger so the location in question may
        very well be present there. If the access misses in every level, main memory is used.

        After a miss, the cache line containing the interesting location is moved to the
        highest level cache, *replacing* a currently present line.

        Neither the programmer nor the compiler need to do anything in order to use a cache,
        which allows (executable) programs to work on machines with different cache
        hierarchies.

        Programming for the cache
        """""""""""""""""""""""""

        While neither programmer nor compiler have to know about caches in order to produce
        correct code, performance can be drastically improved by taking the memory 
        hierarchy into account. Recall that caches are efficient because of the locality
        of most programs, and the more locality the program has, the better the 
        caches work. Here we will discuss how to write code with good locality.

        In general, locality is a function of which memory locations the program accesses 
        as well as in what order the accesses are performed. If all of the locations
        fit in the cache at the same time, only the first reference to each referenced 
        cache line will be a miss. If not everything fits at the same time, the ordering
        matters.

        Imagine that we have a cache with a single cache line and a program that references
        two different memory locations A and B falling in different cache lines. If the
        accesses are in the order A, B, A, B, A, B, ... every access will miss, while if
        the order is A, A, A, ..., B, B, B, ... then there will only be two misses.

        This example may look silly, but since a cache line contains several memory locations
        the A:s might actually be different memory locations falling into the same cache
        line (and similarly for the B:s), a much more common occurrence.

        Blocking
        """"""""

        Pre fetching
        """"""""""""

Modern Processors and  Performance Engineering
^^^^^^^^^^^^^^^^^^

Computer architecture and program performance engineering are intrinsically linked. Understanding computer architecture is vital for several reasons:

From High-Level Language to Machine Code
"""""""""""""""""""""
.. code-block:: plaintext

   +----------------------+  +------------------+  +------------------+  +------------------+
   |                      |  |                  |  |                  |  |                  |
   |   High-Level Code    |  |  Compiler/       |  |  Assembly Code   |  |   Machine Code   |
   | (e.g., C or Python)  |->|  Interpreter     |->|  (Human-readable |->|   (Binary form)  |
   |                      |  |                  |  |  low-level code) |  |                  |
   +----------------------+  +------------------+  +------------------+  +------------------+

- The **High-Level Code** is what programmers usually write.
- A **Compiler or Interpreter** translates this into lower-level representation.
- The result, **Assembly Code**, is specific to the computer's architecture.
- The **Assembler** translates assembly into **Machine Code**.

Machine Code Execution Process
"""""""""""""""""""""

.. code-block:: plaintext

   +--------------------+  +------------------+  +--------------+  +--------------------+
   |                    |  |                  |  |              |  |                    |
   |  Instruction Fetch |->| Instruction      |->| Execution    |->| Result Storage     |
   |   (from Cache/RAM) |  | Decode           |  | Unit         |  | (to Registers/RAM) |
   |                    |  |                  |  |              |  |                    |
   +--------------------+  +------------------+  +--------------+  +--------------------+

- **Instruction Fetch**: CPU gets the next instruction.
- **Instruction Decode**: CPU determines the instruction's meaning.
- **Execution Unit**: Performs the operations.
- **Result Storage**: Saves the output.

Linking Machine Code Execution Process with Performance Engineering
"""""""""""""""""""""

The machine code execution process, as illustrated above, showcases the flow of instructions and data within a computer system. Each component, from the hard disk to the CPU registers, operates at different speeds and has varying sizes. The process's efficiency relies heavily on how these components interact and the path data takes as it moves from one component to the next.

Performance engineering, in its essence, aims to optimize this flow. Here's how:

- **Efficient Data Retrieval**: Performance engineers strategize on how to minimize slow disk or network accesses. This might involve techniques such as data prefetching, where data is preloaded into faster storage (like RAM) before it's needed.

- **Memory Management**: They optimize how programs use the main memory, ensuring that frequently accessed data is readily available, reducing the need to fetch it from slower storage components.

- **Cache Optimization**: A deep understanding of cache hierarchies and their behaviors helps in writing programs that can better utilize the cache. This includes optimizing for spatial and temporal locality, ensuring that the CPU has fewer cache misses.

- **Instruction Parallelism**: By knowing how the CPU executes instructions, engineers can write code that takes advantage of parallel execution units, ensuring that the CPU is kept busy and fully utilized.

In a nutshell, to engineer software that delivers optimal performance on a given hardware, one must understand the intricate dance of instructions and data within that hardware. This underlines the fact that computer architecture and program performance engineering are intrinsically linked. A deep understanding of one aids and enhances the practice of the other.


Stored-program computer architecture
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


The **Stored-Program Computer Architecture**, often referred to as the *Von Neumann Architecture*, is named after John von Neumann. He's credited with the concept of storing program instructions in memory alongside the data upon which they operate. 
- **Memory (RAM)**: Holds both the program instructions and data. It allows both read and write operations.

- **Control Unit (CU)**: Directs operations throughout the computer, using the program's instructions retrieved from memory.

- **Arithmetic Logic Unit (ALU)**: Performs all arithmetic and logical operations, like addition, subtraction, and comparisons.

- **Input and Output (I/O) Systems**: Interfaces through which the computer communicates with the outside world, e.g., keyboards, monitors, and disks.

- **Central Processing Unit (CPU)**: Comprises the ALU and CU. It fetches, decodes, and executes instructions.


.. code-block:: none

   +----------------------------------------------------+
   |                                                    |
   |                        RAM                         |
   |        (stores both data and program code)         |
   |                                                    |
   +----------------------------------------------------+
          ||                         ^     ^
          || Instructions/Data       |     |
          vV                         |     |
   +------------+     +------+
   | Control    |     | ALU  |
   | Unit (CU)  |<--->|      |
   +------------+     +------+
          ||                 ||
          ||                 ||
          vV                 vV
      +--------+         +-------+
      | Input  |         |Output |
      |  I/O   |         |  I/O  |
      +--------+         +-------+

In this representation:

- Arrows represent data and control paths.
- The CPU fetches instructions from RAM.
- Based on these instructions, it might fetch or store data in RAM, perform computations in the ALU, or interact with I/O devices.

.. note:: 
   This is a highly simplified representation. Modern computers have a much more complex architecture, including features like multiple levels of cache, multiple cores, pipelining, and more.


General-purpose cache-based microprocessor architecture
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Stored-Program Computer Architecture, or Von Neumann Architecture, originally had both program data and instructions stored in a single memory and executed instructions sequentially. Over time, to address performance bottlenecks, the evolution led to the General-purpose Cache-based Microprocessor Architecture. This modern design incorporated faster cache memory to speed up frequent data accesses, separated storage for data and instructions to enhance parallel processing, and introduced more streamlined instruction sets for improved execution efficiency. This transition was all in pursuit of greater computational power and efficiency.


Main Components of Cache-based Microprocessor Architecture include

- **CPU Core**: Contains the Control Unit (CU), Arithmetic Logic Unit (ALU), and often other features like floating-point units.

- **Cache Memory**: Typically organized into multiple levels (L1, L2, and sometimes L3 or even L4). L1 is the smallest but fastest, and is directly connected to the CPU core. Subsequent levels are larger and slower.

- **Main Memory (RAM)**: The primary storage for data and instructions, accessed when data is not found in cache.

- **Memory Controller**: Manages communication between the CPU, cache, and main memory.

- **I/O Controllers**: Manage data communication between the CPU and external devices like storage, network interfaces, and peripheral devices.

.. code-block:: none

   +-------------------------+
   |        CPU Core         |
   |     +-------+           |
   |     |  ALU  |           |
   |     +-------+           |
   |     +-------+           |
   |     |  CU   |           |
   |     +-------+           |
   +-------------------------+
           ||          ^
           ||          |
           vV          |
   +------------+      |
   |    L1      |      |
   |   Cache    |------|
   +------------+      |
           ||          |
           vV          |
   +------------+      |
   |    L2      |      |
   |   Cache    |------|
   +------------+      |
           ||          |
           vV          |
   +------------+      |
   |    RAM     |      |
   +------------+      |
           ||          |
           vV          |
   +------------+      |
   | I/O Ctrl   |<-----+
   +------------+

In this representation:

- Arrows represent data and control paths.
- The CPU first checks the L1 cache for data. If not found, it checks the L2 cache.
- If the data isn't in any cache, the CPU fetches it from RAM.
- I/O controllers manage the input/output operations with external devices.

.. note::
   This representation is still a simplification. Real-world architectures might have additional complexities such as multiple cores, more cache levels, specialized processing units, and advanced features for power management and security.


As computing tasks grew in complexity and data size, there was a pressing need to accelerate computing performance. Traditional, sequential methods of processing instructions hit limitations due to physical constraints and inefficiencies. The industry sought innovative approaches to improve throughput, reduce latency, and handle parallelism inherent in many computing tasks. This led to the development and adoption of techniques like pipelining, superscalarity, and SIMD to exploit parallelism and enhance the effective processing capacity of CPUs.

- **Pipelining**: 
  Like an assembly line, it allows different stages of multiple instructions to be processed concurrently, boosting the number of instructions handled per time unit.

- **Superscalarity**: 
  Enables a single CPU to execute more than one instruction per clock cycle by dispatching multiple instructions to appropriate execution units. It's an extension of pipelining, multiplying the work done in a single cycle.

- **Out-of-Order Execution**: 
  Traditional processors execute instructions in the order they are received. However, this sequential approach can be inefficient if certain instructions have to wait for data or resources. With out-of-order execution, CPUs are designed to execute available instructions that have their inputs ready, even if they're not next in sequence. This optimizes the use of CPU resources and boosts overall instruction throughput, even when data for some instructions isn't immediately available.


- **SIMD (Single Instruction, Multiple Data)**: 
  Empowers the CPU to perform the same operation on multiple data elements simultaneously. Ideal for tasks like graphics processing where the same operation is repeated across large datasets.

Memory Hierarchy 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Computer systems employ a memory hierarchy to balance between speed and storage capacity. At the top of this hierarchy is the fastest but smallest memory, while at the bottom is the largest but slowest memory.

.. code-block:: none

    +--------------------+        (1-3 ns)
    |   Registers        |
    +--------------------+
            ||
    +--------------------+        (2-4 ns)
    |   L1 Cache         |
    +--------------------+
            ||
    +--------------------+        (3-20 ns)
    |   L2 Cache         |
    +--------------------+
            ||
    +--------------------+        (10-30 ns)
    |   L3 Cache         |
    +--------------------+
            ||
    +--------------------+        (~100 ns)
    |   Main Memory (RAM)|
    +--------------------+
            ||
    +--------------------+        (~10 ms)
    |   Disk Storage     |
    +--------------------+
            ||
    +--------------------+        (up to several seconds)
    |   Remote Storage   |
    +--------------------+



- The timings provided are approximate and can vary based on the technology and specific configurations used.
- The access time increases as we move down the hierarchy.
- The cost per bit generally decreases as we move down the hierarchy.
- The storage capacity increases as we go down the hierarchy.

.. note::
   The memory hierarchy concept is crucial in computer architecture as it allows systems to have the speed benefits of small, fast memories (like caches) while still benefiting from the large storage capacities of slower memories (like RAM and disk storage).



Cache
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Cache is a smaller, faster type of volatile computer memory that provides high-speed data access to the processor and stores frequently used computer programs, applications, and data. Cache provides faster data storage and access by storing instances of programs and data routinely accessed by the processor.

Cache is a specialized form of volatile computer memory that offers high-speed data access to the processor, enhancing the speed and performance of the computer. By storing instances of frequently accessed programs, applications, and data, cache optimizes the time taken by the processor to retrieve information.

There are different levels of cache based on proximity to the CPU and size. The L1 Cache, integrated directly on the CPU chip, is checked first and offers the fastest access, albeit in a limited size. L2 Cache is typically also on the CPU, slightly larger than L1, but is slower. Meanwhile, the L3 Cache is larger than both L1 and L2 but is slower. It still offers faster access compared to the main memory. Some advanced CPUs also possess L4 caches.

Key technical aspects of cache include its size, often ranging from a few kilobytes to several megabytes; the block size, which dictates how cache is divided; and associativity, which establishes the relationship between main memory blocks and cache lines.

There are various techniques to map data between main memory and cache. Direct Mapped Cache involves a straight correspondence between each block of main memory and a cache line. On the other hand, Fully Associative Cache allows any block of main memory to be loaded into any cache line. Set-Associative Cache is a blend of the two, with cache divided into several sets containing multiple lines.

Cache performance can be further optimized through specific techniques. The write policy outlines the methodology for updating values between cache and main memory, and the replacement policy offers algorithms, such as LRU and FIFO, to determine which cache block to overwrite when new data is fetched.

Mapping Techniques between Main Memory and Cache
"""""""""""""""""""""
- **Direct Mapped Cache**: 
  In this system, each block of the main memory maps to a specific cache line. The decision of which line a block maps to is typically based on the lower bits of the memory address.

  *Example*: Consider a main memory with 16 blocks (numbered 0 to 15) and a cache with 4 lines (numbered 0 to 3). Block 0 of main memory might map to cache line 0, block 1 might map to cache line 1, block 2 to cache line 2, block 3 to cache line 3, and so on. After block 3, the mapping wraps around. Thus, block 4 maps to cache line 0, block 5 maps to cache line 1, and so on.

  *Diagram*:
   
  .. code-block::

     Main Memory       Cache
     -----------       -----
     Block 0  -->   Line 0
     Block 1  -->   Line 1
     Block 2  -->   Line 2
     Block 3  -->   Line 3
     Block 4  -->   Line 0 (wrap around)
     ...
     Block 15 -->   Line 3

- **Fully Associative Cache**: 
  In this type, any block from the main memory can be loaded into any line of the cache.

  *Example*: Block 7 from main memory could reside in cache line 0, or cache line 2, or any other cache line. Similarly, block 11 could reside in any cache line. There's complete flexibility in terms of mapping.

  *Diagram*:

  .. code-block::

     Main Memory       Cache
     -----------       -----
     Block 7  -->   Any Line
     Block 11 -->   Any Line

- **Set-Associative Cache**: 
  Here, the cache is divided into several sets, and each set contains multiple lines. A block from the main memory can be mapped to any line within a specific set.

  *Example*: Consider a 2-way set-associative cache. This means our cache with 4 lines is divided into 2 sets (set 0 and set 1), each containing 2 lines. Block 0 of main memory could map to either line 0 or line 1 of set 0. Block 2 could map to either line 0 or line 1 of set 1.

  *Diagram*:

  .. code-block::

     Main Memory       Cache
     -----------       -----
     Block 0  -->   Set 0 (Line 0 or Line 1)
     Block 2  -->   Set 1 (Line 0 or Line 1)

Multicore Processors
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


A multicore processor is essentially a single computing component with two or more independent actual processing units (known as "cores"), which are the units that read and execute program instructions. Each core can simultaneously execute its own series of instructions. This architecture is devised to improve performance, energy efficiency, and the computational ability of systems processing parallel workloads.

Consider a single-core processor as a single worker capable of handling one task at a time. In contrast, a multicore processor, having multiple cores, is like having multiple workers where each worker can independently handle its own task simultaneously. The true benefit arises when tasks can be split and executed concurrently, leading to faster completion times.

Here's a simplified representation of a multicore processor:

.. code-block::

    +-----------------------------------------+
    |             Processor Chip              |
    |                                         |
    |   +-------+     +-------+    +-------+  |
    |   | Core 1|<--> | Core 2|<-> | Core N|  |
    |   +-------+     +-------+    +-------+  |
    |      ||            ||           ||      |
    |   +-------+     +-------+    +-------+  |
    |   | L1    |     | L1    |    | L1    |  |
    |   +-------+     +-------+    +-------+  |
    |      ||            ||           ||      |
    |   +-----------------------------+       |
    |   |           L2/L3 Cache       |       |
    |   +-----------------------------+       |
    |                  ||                      |
    |   +-----------------------------+       |
    |   | I/O & Memory Controllers    |       |
    |   +-----------------------------+       |
    +-----------------------------------------+




