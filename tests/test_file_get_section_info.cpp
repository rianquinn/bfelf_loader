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

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <bfelf_loader.h>
#include <test_real_elf.h>

TEST_CASE("bfelf_file_get_section_info: invalid elf")
{
    section_info_t info = {};

    auto ret = bfelf_file_get_section_info(nullptr, &info);
    CHECK(ret == BFELF_ERROR_INVALID_ARG);
}

TEST_CASE("bfelf_file_get_section_info: invalid info")
{
    bfelf_file_t ef = {};

    auto ret = bfelf_file_get_section_info(&ef, nullptr);
    CHECK(ret == BFELF_ERROR_INVALID_ARG);
}

TEST_CASE("bfelf_file_get_section_info: not added to loader")
{
    bfelf_file_t ef = {};
    section_info_t info = {};

    auto ret = bfelf_file_get_section_info(&ef, &info);
    CHECK(ret == BFELF_ERROR_INVALID_ARG);
}

TEST_CASE("bfelf_file_get_section_info: expected misc resources")
{
    auto ret = 0LL;
    bfelf_loader_t loader = {};

    auto &&details = load_libraries(&loader, g_filenames);

    ret = bfelf_loader_relocate(&loader);
    CHECK(ret == BFELF_SUCCESS);

    section_info_t info = {};
    auto &&dummy_main_ef = details.back().first;

    dummy_main_ef.init = 10;
    dummy_main_ef.fini = 10;

    ret = bfelf_file_get_section_info(&dummy_main_ef, &info);
    CHECK(ret == BFELF_SUCCESS);

    CHECK(info.init_array_addr != nullptr);
    CHECK(info.init_array_size != 0);

    CHECK(info.fini_array_addr == nullptr);
    CHECK(info.fini_array_size == 0);

    CHECK(info.eh_frame_addr != nullptr);
    CHECK(info.eh_frame_size != 0);
}
