[![GitHub version](https://badge.fury.io/gh/Bareflank%2Fbfelf_loader.svg)](https://badge.fury.io/gh/Bareflank%2Fbfelf_loader)
[![Build Status](https://travis-ci.org/Bareflank/bfelf_loader.svg?branch=master)](https://travis-ci.org/Bareflank/bfelf_loader)
[![Build status](https://ci.appveyor.com/api/projects/status/jfmda57dcl2pjgrc?svg=true)](https://ci.appveyor.com/project/rianquinn/bfelf-loader)
[![codecov](https://codecov.io/gh/Bareflank/bfelf_loader/branch/master/graph/badge.svg)](https://codecov.io/gh/Bareflank/bfelf_loader)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/178552be6c7648e5afad0300a582915c)](https://www.codacy.com/app/rianquinn/bfelf_loader?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Bareflank/bfelf_loader&amp;utm_campaign=Badge_Grade)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/325/badge)](https://bestpractices.coreinfrastructure.org/projects/325)
[![Join the chat at https://gitter.im/Bareflank-hypervisor/Lobby](https://badges.gitter.im/Bareflank-hypervisor/Lobby.svg)](https://gitter.im/Bareflank-hypervisor/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Description

The Bareflank ELF Loader takes cross compiled code (currently code that has
been compiled with --target="x86_64-elf"), loads this code into memory, and
provides a means to then execute this code. The ELF loader supports both
binaries and shared libraries, and can be compiled in C, C++ as well as in user
space and in the kernel. The ELF is also a header-only implementation, and comes
complete with a set of unit tests to ensure it works as expected. Every pull
request is tested on both Windows and Linux via
[AppVeyor](https://ci.appveyor.com/project/rianquinn/bfelf-loader)
and
[Travis CI](https://travis-ci.org/Bareflank/bfelf_loader)
and all of the code goes through a series of checks
including validating code coverage via
[Coveralls](https://coveralls.io/github/Bareflank/hypervisor),
and static / dynamic analysis via
[Coverity](https://scan.coverity.com/projects/bareflank-hypervisor),
[Clang Tidy](http://clang.llvm.org/extra/clang-tidy),
[Coday](https://www.codacy.com/app/rianquinn/bfelf_loader/dashboard),
and
[Google's Sanitizers](https://github.com/google/sanitizers).
Finally, the code adheres to the
[CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/325),
and the
[C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md) and
[SEI Cert C++ Coding Standards](https://www.securecoding.cert.org)
were possible.

To compile this code, perform the following:

```
git clone https://github.com/Bareflank/bfsdk.git
git clone https://github.com/Bareflank/bfsysroot.git
git clone https://github.com/Bareflank/bfelf_loader.git

export PATH="$HOME/bfprefix/bin:$PATH"

mkdir bfsdk/build
mkdir bfsysroot/build
mkdir bfelf_loader/build

pushd bfsdk/buld
cmake ..
make install
popd

pushd bfsysroot/buld
cmake ..
make install
popd

pushd bfelf_loader/buld
cmake ..
make install
make test
popd
```

## Dependencies

The ELF loader's code depends on a set of headers located in the
[Bareflank SDK](https://github.com/Bareflank/bfsdk).
Specifically these headers are:

```cpp
#include <bftypes.h>
#include <bfconstants.h>
#include <bferrorcodes.h>
#include <bfsupport.h>
```

These headers provide generic support for types, some constants, error codes
and some structures used by the ELF loader for handling constructors and
destructors. If you wish to use the ELF loader independently, these headers
should be installed on the system to support the ELF loader (or simply
prepended to it).

The ELF loader's unit tests rely on the presence of the
[Bareflank Sysroot](https://github.com/Bareflank/bfsysroot)
which provides the C++ libraries that are used by Bareflank. The unit tests
are optional, but if you wish to use them, you will need to install the
sysroot in addition to the full SDK.

In order for the rest of the build system to find the this prefix, it's bin
directory should be added to your path (best to add this to your .bashrc)

#### Linux
```
export PATH="$HOME/bfprefix/bin/:$PATH"
```

#### Windows
```
set PATH=%HOMEPATH%\bfprefix\bin;%PATH%
```


## License

The Bareflank Hypervisor is licensed under the GNU Lesser General Public License
v2.1 (LGPL).
