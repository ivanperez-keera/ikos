INSTALL IKOS ON RED HAT ENTERPRISE LINUX 6.8
============================================

Here are the steps to install IKOS and its dependencies on **Red Hat Enterprise Linux 6.8**

IKOS requires certain versions of gcc, boost, python and llvm that are newer than the ones available on the Red Hat Yum package manager. Hence the following describes the steps to bootstrap these dependencies on Red Hat.

**Warning**: You will need **at least 10 Gb** of disk space and a **few hours**.

First, make sure your system is up-to-date:

```
$ sudo yum update
```

Now, install the following packages using yum:

```
$ sudo yum install which patch tar bzip2 xz zlib-devel ncurses-devel sqlite-devel gmp-devel gcc gcc-c++ cmake
```

The next step will use the bootstrap script to build and install gcc, boost, python, llvm and IKOS.
Here, we will use `/path/to/ikos-install` as the installation directory and `/path/to/ikos-build` as the build directory. Replace it with the location where you want to put IKOS and its dependencies (for instance, `~/ikos-install` and `~/ikos-build`).

In IKOS root directory, run:

```
$ cd scripts
$ ./bootstrap --prefix=/path/to/ikos-install --builddir=/path/to/ikos-build
```

You can also specify the number of CPU you want to use with `--jobs=N`. By default, it will use **all available CPU**.

Note: Try to avoid whitespaces in the installation path, as it might fail.

This script will also build and install IKOS for you.

After installation, the install directory will contain the following structure:

```
.
├── activate-full
├── activate-minimal
├── boost-1.61.0
│   ├── include
│   └── lib
├── gcc-6.1.0
│   ├── bin
│   ├── include
│   ├── lib
│   ├── lib64
│   ├── libexec
│   └── share
├── ikos-1.2
│   ├── bin
│   ├── include
│   └── lib
├── libedit-2.11
│   ├── include
│   ├── lib
│   └── share
├── llvm-3.7.1
│   ├── bin
│   ├── include
│   ├── lib
│   └── share
└── python-2.7.12
    ├── bin
    ├── include
    ├── lib
    └── share
```

During its execution, the **bootstrap** script creates a special environment with all the required dependencies for IKOS. To enter that environment, simply run the following command (consider adding this in your `.bashrc`):

```
source /path/to/ikos-install/activate-minimal
```

For short, it adds the necessary directories to your `PATH` and your `LD_LIBRARY_PATH`.

For more information about the **bootstrap** script and how to run the tests, see `docs/INSTALL_ROOTLESS.md`.

You are now ready to use IKOS. Go to the section `How to Run IKOS` of the `README.md`.
