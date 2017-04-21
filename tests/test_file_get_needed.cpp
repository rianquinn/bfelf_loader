//
// Bareflank Hypervisor
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <catch/catch.hpp>

#include <fstream>
#include <test_real_elf.h>

TEST_CASE("bfelf_file_get_needed: invalid elf file")
{
    const char *needed;
    uint64_t index = 0;

    auto ret = bfelf_file_get_needed(nullptr, index, &needed);
    CHECK(ret == BFELF_ERROR_INVALID_ARG);

    std::cout << BAREFLANK_SYSROOT_PATH << '\n';
}

TEST_CASE("bfelf_file_get_needed: index")
{
    const char *needed;
    uint64_t index = 0;
    bfelf_file_t ef = {};

    auto ret = bfelf_file_get_needed(&ef, index, &needed);
    CHECK(ret == BFELF_ERROR_INVALID_INDEX);
}

TEST_CASE("bfelf_file_get_needed: invalid size")
{
    uint64_t index = 0;
    bfelf_file_t ef = {};

    auto ret = bfelf_file_get_needed(&ef, index, nullptr);
    CHECK(ret == BFELF_ERROR_INVALID_ARG);
}

TEST_CASE("bfelf_file_get_needed: success")
{
    auto ret = 0LL;
    bfelf_loader_t loader = {};

    auto &&binaries = bfelf_load_binaries(&g_file, g_filenames, &loader);
    auto &&main_binary = binaries.back();

    ret = bfelf_loader_relocate(&loader);
    CHECK(ret == BFELF_SUCCESS);

    const char *needed;
    uint64_t index = 0;

    ret = bfelf_file_get_needed(&main_binary->ef(), index, &needed);
    CHECK(ret == BFELF_SUCCESS);
}
