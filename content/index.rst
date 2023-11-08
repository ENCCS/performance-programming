Performance Programming
=======================

In this lesson, you will learn to write efficient programs. Or at least get a first impulse; only by applying these
techniqes in your own code you will truly understand them. It is also not just a set of techniques, but a mind set
that you will acquire by using it.

We will deal with efficiency on several different levels:

- Algorithm: What are the basic steps your program performs and how are the data structures organized?
- Compiler: What can the compiler do for you, and how can you help it?
- Hardware: How does a modern processor work, and how can you adapt your program to it?
- Performance analysis: Does your program run in the way you intended?

We will address these questions in a language and architecture agnostic way as far as possible, with code
examples in C (and Fortran, when I have brushed up a bit). Our main architectural example will be the x86
and its implementations.

.. prereq::

   Before attending this workshop, please make sure that you have access
   to a computer with a C or Fortran compiler installed. Linux would be the
   preferred operating system, but at least the algorithm part should be 
   reasonably OS independent. Performance measurement works best when not run
   on a virtual machine; a dedicated machine like an ordinary laptop works
   just fine.


.. toctree::
   :maxdepth: 1
   :hidden:
   
   setup

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: The lesson

   algorithms
   compilers
   architecture
   tuning


.. csv-table::
   :widths: auto
   :delim: ;

   20 min ; :doc:`algorithms`
   10 min ; :doc:`compilers`
   20 min ; :doc:`architecture`
   10 hrs ; :doc:`tuning`

.. toctree::
   :maxdepth: 1
   :caption: Reference

   quick-reference
   guide



.. _learner-personas:

Who is the course for?
----------------------

This lesson material is targeted towards students, researchers, engineers, and
developers who write programs that they would like to run faster. The focus of the
course is on mid level languages like C, C++, Fortran and so on, but most of the
issues discussed are relevant for assebly code, and at least the algorithm part can
be useful for code written in high level languages such as Julia and Haskell.

The course assumes familiarity with C or Fortran syntax which is used for the code
examples, but no knowledge of computer architecture or complexity theory is needed.


About the course
----------------

This lesson material is developed by the `EuroCC National Competence
Center Sweden (ENCCS) <https://enccs.se/>`_ and taught in ENCCS
workshops. Each lesson episode has clearly defined learning
objectives and includes multiple exercises along with solutions, and
is therefore also useful for self-learning.
The lesson material is licensed under `CC-BY-4.0
<https://creativecommons.org/licenses/by/4.0/>`_ and can be reused in any form
(with appropriate credit) in other courses and workshops.
Instructors who wish to teach this lesson can refer to the :doc:`guide` for
practical advice.


See also
--------




Credits
-------

The lesson file structure and browsing layout is inspired by and derived from
`work <https://github.com/coderefinery/sphinx-lesson>`__ by `CodeRefinery
<https://coderefinery.org/>`__ licensed under the `MIT license
<http://opensource.org/licenses/mit-license.html>`__. We have copied and adapted
most of their license text.

Instructional Material
^^^^^^^^^^^^^^^^^^^^^^

This instructional material is made available under the
`Creative Commons Attribution license (CC-BY-4.0) <https://creativecommons.org/licenses/by/4.0/>`__.
The following is a human-readable summary of (and not a substitute for) the
`full legal text of the CC-BY-4.0 license
<https://creativecommons.org/licenses/by/4.0/legalcode>`__.
You are free to:

- **share** - copy and redistribute the material in any medium or format
- **adapt** - remix, transform, and build upon the material for any purpose,
  even commercially.

The licensor cannot revoke these freedoms as long as you follow these license terms:

- **Attribution** - You must give appropriate credit (mentioning that your work
  is derived from work that is Copyright (c) ENCCS and individual contributors and, where practical, linking
  to `<https://enccs.github.io/sphinx-lesson-template>`_), provide a `link to the license
  <https://creativecommons.org/licenses/by/4.0/>`__, and indicate if changes were
  made. You may do so in any reasonable manner, but not in any way that suggests
  the licensor endorses you or your use.
- **No additional restrictions** - You may not apply legal terms or
  technological measures that legally restrict others from doing anything the
  license permits.

With the understanding that:

- You do not have to comply with the license for elements of the material in
  the public domain or where your use is permitted by an applicable exception
  or limitation.
- No warranties are given. The license may not give you all of the permissions
  necessary for your intended use. For example, other rights such as
  publicity, privacy, or moral rights may limit how you use the material.


Software
^^^^^^^^

Except where otherwise noted, the example programs and other software provided
with this repository are made available under the `OSI <http://opensource.org/>`__-approved
`MIT license <https://opensource.org/licenses/mit-license.html>`__.
