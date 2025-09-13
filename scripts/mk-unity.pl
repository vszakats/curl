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

my @allsrc;
my @test;
my @include;
my $batches = 1;
my $outprefix = '_out-N.c';

GetOptions(
    'test=s{,}'    => \@test,
    'include=s{,}' => \@include,
    'batches=i'    => \$batches,
    'outprefix=s'  => \$outprefix,
) or die "Usage: $0 [--batches=N] [--test <tests>] [--include <include-c-sources>]\n";

@include = grep { $_ =~ '([a-z0-9_]+)\.c$' } @include;
push @allsrc, @include, @test;
my %include = map { $_ => 1 } @include;

my $files_per_batch = int(scalar @allsrc / $batches);

my $pos = 0;

for my $i (1..$batches) {

    my $outfn = $outprefix;
    $outfn =~ s/N/$i/;
    open my $out, '>', $outfn or die "Failed to create $outfn: $!";

    print $out "/* !checksrc! disable COPYRIGHT all */\n\n";

    my $tlist = "";
    if(scalar @test && $i == 1) {
        print $out "#include \"first.h\"\n\n";

        foreach my $src (@allsrc) {
            if($src =~ /([a-z0-9_]+)\.c$/) {
                my $name = $1;
                if(not exists $include{$src}) {  # register test entry function
                    $tlist .= "  {\"$name\", test_$name},\n";
                    print $out "CURLcode test_$name(const char *arg);\n"
                }
            }
        }
        print $out "\n";
    }

    if($i == $batches) {
        $files_per_batch = scalar @allsrc - $pos;
    }

    for my $i (1..$files_per_batch) {
        my $src = $allsrc[$pos++];
        if($src =~ /([a-z0-9_]+)\.c$/) {
            my $name = $1;
            print $out "#include \"$src\"\n";
        }
    }

    if(scalar @test && $i == 1) {
        print $out "\nconst struct entry_s s_entries[] = {\n$tlist  {NULL, NULL}\n};\n";
        print $out "\n#include \"first.c\"\n";
    }

    close $out or warn "Failed to close $outfn: $!";
}
