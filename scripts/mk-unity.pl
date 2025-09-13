#!/usr/bin/env perl
#***************************************************************************
#                                  _   _ ____  _
#  Project                     ___| | | |  _ \| |
#                             / __| | | | |_) | |
#                            | (__| |_| |  _ <| |___
#                             \___|\___/|_| \_\_____|
#
# Copyright (C) Viktor Szakats
#
# This software is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at https://curl.se/docs/copyright.html.
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the COPYING file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
# SPDX-License-Identifier: curl
#
###########################################################################

# Helper script for "unity"-like support in autotools and to bundle up tests
# for both autotools and cmake. It generates the umbrella C source that
# includes the individual source files and tests.

use strict;
use warnings;
use Getopt::Long;

my @src;
my @test;
my @include;

GetOptions(
    'test=s{,}'    => \@test,
    'include=s{,}' => \@include,
) or die "Usage: $0 [--test <tests>] [--include <include-c-sources>]\n";

push @src, @include, @test;
my %include = map { $_ => 1 } @include;

print "/* !checksrc! disable COPYRIGHT all */\n\n";
if(scalar @test) {
    print "#include \"first.h\"\n\n";
}

my $tlist = "";

foreach my $src (@src) {
    if($src =~ /([a-z0-9_]+)\.c$/) {
        my $name = $1;
        print "#include \"$src\"\n";
        if(not exists $include{$src}) {  # register test entry function
            $tlist .= "  {\"$name\", test_$name},\n";
        }
    }
}

if(scalar @test) {
    print "\nconst struct entry_s s_entries[] = {\n$tlist  {NULL, NULL}\n};\n";
    print "\n#include \"first.c\"\n";
}
