// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

#include "build.hpp"

#include <algorithm>
#include <fstream>
#include <random>

#include <cereal/archives/binary.hpp>
#include <hibf/config.hpp>
#include <hibf/interleaved_bloom_filter.hpp>

void build(config const & config)
{
    auto get_user_bin_data = [&](size_t const user_bin_id, seqan::hibf::insert_iterator it)
    {
        std::uniform_int_distribution<uint64_t> distrib{};
        std::mt19937_64 gen{user_bin_id};
        auto random = [&]()
        {
            return distrib(gen);
        };
        std::ranges::generate_n(it, config.elements, random);
    };

    seqan::hibf::config ibf_config{.input_fn = get_user_bin_data,
                                   .number_of_user_bins = config.user_bins,
                                   .number_of_hash_functions = 2u,
                                   .maximum_fpr = 0.05,
                                   .threads = config.threads};

    seqan::hibf::interleaved_bloom_filter ibf{ibf_config};

    std::ofstream output_stream{config.index_path, std::ios::binary};
    cereal::BinaryOutputArchive archive{output_stream};
    archive(ibf);
}
