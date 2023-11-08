Setting up your system
======================

In order to follow this workshop, you will need personal computer for the exercises.
This means that you should access to C and Fortran compilers in your computer.
You can use an HPC cluster if you have access to one, but the installation instructions
descried below cover how to install the prerequisites on your own computer.


For Linux users
^^^^^^^^^^^^^^^^^^^^^^^^

Both C and Fortran compilers are usually installed in Linux and Unix OS by default.
Just in case there is no compilers installed in your computer, you should follow the
instructions below to install compilers.

The GCC Compiler (GNU Compiler Collection) is a collection of compilers and libraries
capable of compiling programs written in C, C++, GO, Fortran, and Objective-C programming languages.
It is distributed under the GNU General Public License.

You can follow the instructions `HERE <https://www.scaler.com/topics/c/install-c-on-linux/>`__ at this link to install the GCC Compiler.


For Mac users
^^^^^^^^^^^^^

Here is the `guide <https://fastbitlab.com/microcontroller-embedded-c-lecture-10-installing-compiler-gcc-for-host-mac/>`__ to install GCC compilers on a Mac using Homebrew.

- Install Homebrew
  - Open the **terminal** on your mac computer
  - Copy and paste the following command to the **terminal** app, and then press enter/return key
  - `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
    - Wait for the command to finish
    - If you are prompted to enter a password, please type your mac user's login password and press ENTER.
    - Mind you, as you type your password, it won't be visible on your Terminal (for security reasons), but rest assured it will work.
  - Copy/paste and run this command to make brew command available inside the Terminal
  - `echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile`
- After Homebrew installs, type `brew install gcc` in the **terminal**
- Once the install completes, you can check the installed compilers via the commands
  - `gcc --version`
  - `which gfortran`


For Windows users
^^^^^^^^^^^^^^^^^

There are three options to install GCC compilers in your windows computer.

- 1. You can install the MinGW Utility in your computer.
  - Here are the detailed `guidelines <https://linuxhint.com/install-gcc-windows/>`__.
- 2. You can install **Cygwin**, which gives us a Unix-like environment running on Windows.
  - Then follow `steps <https://preshing.com/20141108/how-to-install-the-latest-gcc-on-windows/>`__ to install GCC compilers.
- 3. You can install **MobaXterm**, which provides a good Linux shell for the Windows operating system.
  - After the installation, download plugins and follow procedures at `HERE <https://mobaxterm.mobatek.net/plugins.html>`__
