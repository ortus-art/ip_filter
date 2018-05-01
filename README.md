# ip_filter project

[![Build Status][travis-badge]][travis-link]
[![codecov][codecov-badge]][codecov-link]
[![License: GPL v3][license-badge]](LICENSE.md)
[![Download][bintray-badge]][bintray-link]

Ip address filtering sample.
## Requirements

It takes preformatted data from standard input. 

The data has following format: 
* A new line marks start of a new data
* The line starts with IPv4 string
* The data that follows after the IP address is separated by tabs

In addtion the solution should use new C++ features where possible. This includes:
* Variadic templates (Must)
* Lambdas
* Etc.

The input data has to be:
1. parsed, 
2. sorted in reversed order, 
3. filtered. 

It has to output the data to the stadard output. It outputs all data and three hardcoded filters:
1. The first octet is equal to 1
2. The first octet is 46, second - 70
3. Any octet that is equal to 46


The solution is veryfied by running against the provided test data. 

The result against the test data can be verified by using the following or similar command
```shell
[[ $(ip_filter < data.tsv | md5sum) =~ "24e7a7b2270daee89c64d3ca5fb3da1a" ]] && echo OK
```


## Implementation

Currently it has only limited error handling. Most simple and obvious cases are handled. 

All parsing errors are logged into the standard error stream.

The code is covered by tests. However, the tests are limited in nature. They cover mostly only the cases that are defined by requirements. 

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