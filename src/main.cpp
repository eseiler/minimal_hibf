// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

#include <iostream>

#include <sharg/exceptions.hpp>

#include "run.hpp"

int main(int argc, char ** argv)
{
    try
    {
        run({argv, argv + argc});
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << '\n';
        return -1;
    }

    return 0;
}
