Algorithms
----------

The first step towards writing efficient code is to start from a good algorithm. It is also where
the most dramatic performance improvements can be found.

Sometimes good 
algorithms are available in libraries and the only thing one needs to do is to call them. But when
you write code to solve a new problem, or an old problem in a new way, you are on your own.

Hence this chapter of the lesson is about algorithms, or rather about algorithmic patterns.

Complexity
^^^^^^^^^^

Algorithms are often categorized by their *complexity*, meaning their execution time as a function of
the size of the input. Since the actual running time varies between systems, the execution time we use
in this context is the number of steps that an idealized (model of a) computer called a Random Access Machine,
or *RAM*, would need. Input sizes are measured in different ways for different algorithms.

  For a naive
  simulation of gravitational attraction between a large number of stars, the size of the problem is typically
  the number of stars. Since every star is attracted by every other star, the work for a single time
  step of the simulation is proportional to the square of the number of stars.

  As an alternative, one could imagine doing the force calculation by dividing space into a number of fixed
  size cells and compute the force on each star by considering the mass of stars in each cell. The cost of
  doing that for one star would be proportional to the number of cells, thus the size and the granularity
  of the simulated space becomes part of the size of the problem for this alternative approach.

  Later, we will encounter the Barnes-Hut algorithm which combines these two approaches in a clever way.



Actual computers differ from the RAM and from each other in many details, and these have important
consequences for performance, as we will see later in this lesson. However, almost always the difference
can be expressed as a constant multiplicative factor. That is, one machine is about :math:`X` times faster than
another independent of the size of the input.

Thus, when we discuss the complexity of an algorithm, we are not interested in absolute performance
but rather in how the execution time changes when the size of the input changes. This is typically expressed using
the "big O" notation; we write that the naive gravity simulation algorithm above is :math:`O(n^2)` to mean that
for large enough :math:`n` there is a constant :math:`c` such that the algorithm uses at most :math:`cn^2` steps
on a RAM to solve a problem of size :math:`n`. The "large enough" provisio captures the fact that we are interested
in what happens "in the limit". Technically, it for instance allows us to amortize
any fixed cost initialization over the entire computation.

Case study: Are the elements of an array unique?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Consider the problem of determining if the elements of an array of interǵers are all unique. Here is a simple
version that compares all pairs of elements:

.. code-block:: C

  int unique1(int a[], int n) {
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(i != j && a[i] == a[j]) return 0;
    return 1;
  }

Complexity is quadratic (:math:`n^2`) due to the nested loops. Some of the computation is clearly redundant,
each pair (x,y) of distict indices is checked twice, once when `i==x` and `j==y` and once when `i==y`
and `j==x`. So the first improvement is to remove this simple redundancy:

.. code-block:: C

  int unique2(int a[], int n) {
    for(int i = 0; i < n-1; i++)
      for(int j = i+1; j < n; j++)
        if(a[i] == a[j]) return 0;
    return 1
  }

Here we insist that `i<j` at all times so we check each (x,y) pair only once and also at the same time
we avoid the test ensuring that `i != j`. Can we do better? Yes, by sorting the array first. Sorting
can be accomplished in time :math:`O(n \log(n))` which is much faster than :math:`O(n^2)`. Having sorted the
array, equal elements are now adjacent.

.. code-block:: C

  int unique3(int a[], int n) {
    sort(a, n);
    for(int i = 1; i < n; i++ ) {
      if(a[i-1] == a[i]) return 0;
    }
    return 1;
  }

Here we helped ourselves to a function ``sort()`` that sorts an array of ``int``. There are interesting lessons
to learn from implementing that function, and we will return to these later.

What is the complexity of ``unique3()``? The function first sorts the array, then traverses it linearly in a single
pass, a process that is clearly :math:`O(n)`. If the algorithm used by ``sort()`` is :math:`O(n\log(n))`, this means
that the entire algorithm is :math:`O(n\log(n))` since this is asymptotically greater. There is no constant :math:`c`
such that :math:`cn > n\log(n)` for large :math:`n`.

Is there a way to solve this problem even faster? There is at least one variation that is likely to be faster in many
cases, and that involves using a *hash table*. This is a data structure that can be used to implement a set with fast
insert, delete, and membership test (in general, a hash table can implement a finite map from a set of *keys* to a set of
arbitrary values).

The new version iterates over the integers in the array one by one, looks up each one in the hash table and inserts it if
it was not there.

.. code-block:: C

  int unique4(int a[], int n) {
    ht_t h = new_hash_table(n);
    for(int i = 0; i < n; i++ ) {
      if(member(h, a[i])) return 0;
      insert(h, a[i]);
    }
    delete_hash_table(h);
    return 1;
  }
    
A hash table is implemented as an array that is indexed using a hash value computed from the object we want to
insert or check membership for. The hash value must be a valid index into the table, so if the size of the table is
:math:`s` then the hash value :math:`v` must satisfy :math:`0 \leq v < s`.

In general, we compute a hash value in two steps. First we compute an integer :math:`k` from the
object we want to insert. In this example, we already have an integer, so this this
step becomes trivial. Second, we limit the size by for instance taking the modulus
with respect to the table size :math:`s` of :math:`k` to get a valid index.


