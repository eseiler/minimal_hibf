<!--
SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
SPDX-License-Identifier: CC0-1.0
-->

# minimal_hibf [![build status][1]][2] [![codecov][3]][4]
<!--
    Above uses reference-style links with numbers.
    See also https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links.

    For example, `[![build status][1]][2]` evaluates to the following:
        `[link_text][2]`
        `[2]` is a reference to a link, i.e. `[link_text](https://...)`

        `[link_text]` = `[![build status][1]]`
        `[1]` is once again a reference to a link - this time an image, i.e. `[![build status](https://...)]
        `![build status]` is the text that should be displayed if the linked resource (`[1]`) is not available

    `[![build status][1]][2]` hence means:
    Show the picture linked under `[1]`. In case it cannot be displayed, show the text "build status" instead.
    The picture, or alternative text, should link to `[2]`.
-->

<!--
    This is the CI badge image:
        `https://img.shields.io/github/workflow/status/` - we do not use GitHub's badges as they are not customisable.
        `/eseiler/minimal_hibf/` - owner/repository
        `CI%20on%20Linux` - name of the workflow as encoded URL (e.g., whitespace = %20)
        `main` - branch to show
        `?style=flat&logo=github` - use a GitHub-style badge
        `&label=minimal_hibf%20CI` - text on the badge
        `"Open GitHub actions page"` - this text will be shown on hover
-->
[1]: https://img.shields.io/github/actions/workflow/status/eseiler/minimal_hibf/ci_linux.yml?branch=main&style=flat&logo=github&label=minimal_hibf%20CI "Open GitHub actions page"
<!--
    This is the CI badge link:
        `https://github.com/eseiler/minimal_hibf/actions` - actions page of owner/repository
        `?query=branch%3Amain` - only show actions that ran on the mater branch
-->
[2]: https://github.com/eseiler/minimal_hibf/actions?query=branch%3Amain
<!--
    This is the Codecov badge image:
        Codecov offers badges: https://app.codecov.io/gh/eseiler/minimal_hibf/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the image part of the markdown badge here.
    `"Open Codecov page"` - this text will be shown on hover
-->
[3]: https://codecov.io/gh/eseiler/minimal_hibf/branch/main/graph/badge.svg "Open Codecov page"
<!--
    This is the Codecov badge link:
        Codecov offers badges: https://app.codecov.io/gh/eseiler/minimal_hibf/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the URL part of the markdown badge here.
-->
[4]: https://codecov.io/gh/eseiler/minimal_hibf

# Build

```bash
git clone https://github.com/eseiler/minimal_hibf
cd minimal_hibf
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j
```

# Use

```bash
# Inside build directory

# IBF with 256 bins and 10000 random elements each
./minimal_hibf build --output index --element 10000 --bins 256 --threads 2

# Query a single query of 5000 random elements. This is done 100 times inside a parallel for loop.
./minimal_hibf search --input index --elements 5000 --queries 100 --threads 2
```
