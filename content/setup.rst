Setup
-----

In order to follow this workshop, you will need personal computer for the exercises.
This means that you should access to C and Fortran compilers in your computer.

You can use an HPC cluster if you have access to one, but the installation instructions
descried below cover how to install C and Fortran compilers in your own computer.

The GCC compiler (GNU Compiler Collection) is a collection of compilers and libraries
capable of compiling programs written in C, C++, GO, Fortran, and Objective-C programming languages.
It is distributed under the GNU General Public License.

The detailed installation procedures in Linux OS, MacOS and Windows OS are listed below.

Note that it is unlikely that the ``perf`` utility which is used in the course will
work correctly under Windows. In that case, you can always use ``time`` to measure
execution time, but it will not give data collected by the hardware performance counters.


For Linux users
^^^^^^^^^^^^^^^

Both C and Fortran compilers are usually installed in Linux and Unix OS.
Just in case there is neither C nor Fortran compilers in your computer,
you can follow the instructions `HERE <https://www.scaler.com/topics/c/install-c-on-linux/>`_ to install the GCC compiler.


For Mac users
^^^^^^^^^^^^^

`HERE <https://fastbitlab.com/microcontroller-embedded-c-lecture-10-installing-compiler-gcc-for-host-mac/>`_
in the guide to install GCC compiler using Homebrew.

- Install Homebrew
    - Open the **terminal** on your mac computer
    - Copy/paste and run the command at the **terminal** ``/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"``
    - Wait for the command to finish. If you are prompted to enter a password, please type your mac user's login password.
    - Copy/paste and run the command to make brew command available inside the **terminal** ``echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile``

- After Homebrew installs, type ``brew install gcc`` in the **terminal**

- Once the installation completes, you can check the installed compilers via the commands
    - ``gcc --version``
    - ``which gfortran``


For Windows users
^^^^^^^^^^^^^^^^^

There are three options to install GCC compilers in your windows computer.

- 1. You can install the **MinGW Utility** in your computer.
  The detailed guidelines at `HERE <https://linuxhint.com/install-gcc-windows/>`_.

- 2. You can install **Cygwin**, which gives us a Unix-like environment running on Windows.
  Then follow steps at `HERE <https://preshing.com/20141108/how-to-install-the-latest-gcc-on-windows/>`_
  to install GCC compilers.

- 3. You can install **MobaXterm**, which provides a good Linux shell for the Windows operating system.
  After the installation, follow steps at `HERE <https://mobaxterm.mobatek.net/plugins.html>`_
  to download plugins and put them in the same directory that MobaXterm executable.

