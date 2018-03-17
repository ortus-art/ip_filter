# ip_filter project

[![Build Status][travis-badge]][travis-link]
[![codecov][codecov-badge]][codecov-link]
[![License: GPL v3][license-badge]](LICENSE.md)
[![Download][bintray-badge]][bintray-link]

Ip address filtering sample.

It takes preformatted data, filters out IP addresses and sorts them.

The data is taken from the standard input and outputted to the standard output.

It expects following format of the data: each text row starts with IP address, which is followed by whitespace and other text until the end of line.

At this stage all badly formatted data is ignored.

## Usage sample

```shell
$ cat <tabular_data.tcv> | ip_filter
```

[travis-badge]:    https://travis-ci.org/ortus-art/ip_filter.svg?branch=master
[travis-link]:     https://travis-ci.org/ortus-art/ip_filter
[license-badge]:   https://img.shields.io/badge/License-GPL%20v3-blue.svg
[codecov-badge]:   https://codecov.io/gh/ortus-art/ip_filter/branch/master/graph/badge.svg
[codecov-link]:    https://codecov.io/gh/ortus-art/ip_filter
[bintray-badge]:   https://api.bintray.com/packages/ortus-art/course/ip_filter/images/download.svg
[bintray-link]:    https://bintray.com/ortus-art/course/ip_filter/_latestVersion