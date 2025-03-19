// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

#include "search.hpp"

#include <algorithm>
#include <fstream>
#include <random>

#include <cereal/archives/binary.hpp>
#include <hibf/interleaved_bloom_filter.hpp>

void search(config const & config)
{
    seqan::hibf::interleaved_bloom_filter ibf{};
    {
        std::ifstream input_stream{config.index_path, std::ios::binary};
        cereal::BinaryInputArchive archive{input_stream};
        archive(ibf);
    }

    std::vector<uint64_t> const query = [](size_t const size)
    {
        std::vector<uint64_t> result(size);
        std::uniform_int_distribution<uint64_t> distrib{};
        std::mt19937_64 gen{0u};
        auto random = [&]()
        {
            return distrib(gen);
        };

        std::ranges::generate(result, random);
        return result;
    }(config.elements);

#pragma omp parallel num_threads(config.threads)
    {
        auto agent = ibf.counting_agent();
#pragma omp for
        for (size_t i = 0; i < config.num_queries; ++i)
        {
            [[maybe_unused]] auto & result = agent.bulk_count(query);
        }
    }
}
