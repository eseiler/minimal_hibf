// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <filesystem>

struct config
{
    std::filesystem::path index_path{"index"};
    size_t elements{1000u};
    size_t user_bins{128u};
    size_t num_queries{10u};
    size_t threads{1u};
};
