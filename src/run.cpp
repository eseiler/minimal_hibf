// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

#include "run.hpp"

#include <sharg/all.hpp>

#include "build.hpp"
#include "config.hpp"
#include "search.hpp"
#include "validator.hpp"

void run(std::vector<std::string> const & arguments)
{
    config config{};

    sharg::parser parser{"minimal_hibf", arguments, sharg::update_notifications::off, {"build", "search"}};
    parser.parse();

    sharg::parser & sub_parser = parser.get_sub_parser();

    if (sub_parser.info.app_name == std::string_view{"minimal_hibf-build"})
    {
        sub_parser.add_option(config.index_path,
                              sharg::config{.short_id = '\0',
                                            .long_id = "output",
                                            .description = "Where to store the index.",
                                            .validator = sharg::output_file_validator{}});
        sub_parser.add_option(config.elements,
                              sharg::config{.short_id = '\0',
                                            .long_id = "elements",
                                            .description = "How many values per user bin.",
                                            .validator = positive_integer_validator{}});
        sub_parser.add_option(config.user_bins,
                              sharg::config{.short_id = '\0',
                                            .long_id = "bins",
                                            .description = "How many user bins.",
                                            .validator = positive_integer_validator{}});
        sub_parser.add_option(config.threads,
                              sharg::config{.short_id = '\0',
                                            .long_id = "threads",
                                            .description = "How many threads to use.",
                                            .validator = positive_integer_validator{}});
        sub_parser.parse();
        build(config);
    }
    else if (sub_parser.info.app_name == std::string_view{"minimal_hibf-search"})
    {
        sub_parser.add_option(config.index_path,
                              sharg::config{.short_id = '\0',
                                            .long_id = "input",
                                            .description = "Path to the index.",
                                            .validator = sharg::input_file_validator{}});
        sub_parser.add_option(config.elements,
                              sharg::config{.short_id = '\0',
                                            .long_id = "elements",
                                            .description = "How elements a query contains.",
                                            .validator = positive_integer_validator{}});
        sub_parser.add_option(
            config.num_queries,
            sharg::config{.short_id = '\0',
                          .long_id = "queries",
                          .description = "How often the query is searched. There is only a single query which is "
                                         "`queries` often times searched in a parallel for loop.",
                          .validator = positive_integer_validator{}});
        sub_parser.add_option(config.threads,
                              sharg::config{.short_id = '\0',
                                            .long_id = "threads",
                                            .description = "How many threads to use.",
                                            .validator = positive_integer_validator{}});
        sub_parser.parse();
        search(config);
    }
}
