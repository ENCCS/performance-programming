Tuning
------

Note: This file collects material that should be reorganized later.

Matrix matrix multiplication
============================

Here is a naive matrix multiply with the same structure as the classic definition. The
outer two loops iterate over the result array while the innermost loop computes the
sum.

.. literalinclude:: ex-mm-ref.c
   :language: C
   :linenos:

You can build this code using the following command:

.. code-block:: bash

   gcc -O -o mm ex-mm-ref.c ex-mm-main.c -lm

This gives you an executable program called ``mm``.

.. exercise::

   Try running ``mm`` with different sized inputs and measure the execution time
   using the ``time`` command. Sizes around 1000 should run in a few seconds.

.. solution::

   On my laptop, I get the following:
   
   .. image:: mm1-times.png
      :align: center

   |
   
   Same data in tabular form:
   
   .. csv-table::
      :file: mm1-times.dat
      :delim: space
      :header: "Size", "Time (seconds)"
      :align: center
   
   You can have a different shape to your curve; maybe it starts growing steeper
   at some point. This likely depends on the memory hierarchy of your machine.

We know from inspecting the code that matrix multiplication is cubic in the size of
the matrix (for square matrices). Does that theory hold in practice as well?

.. exercise::

   Try to fit a cubic function (degree three polynomial) to the measurements in
   the previous exercise.

.. solution::


   On my laptop, I get the following:
   
   .. image:: mm1-times-c.png
      :align: center
      
   I did the fitting by hand, prioritizing the smaller matrix sizes since 
   the larger sizes likely have longer per-iteration times due to more
   cache misses. The difference is not dramatic, though, as you can see.

Foo   
