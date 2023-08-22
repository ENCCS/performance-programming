Architecture
------------

This part gives an overview of computer architecture including common implementation
techniques and how to adapt code to get the best performance from them.

A crash course in computer architecture
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

