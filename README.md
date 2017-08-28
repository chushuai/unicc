*unicc*: Universal LALR(1) Parser Generator

SYNOPSIS
========

unicc \[OPTION\]... FILE

ABOUT
=====

UniCC is a LALR(1) parser generator and language development system.

Its design-goal is to serve as an all-round design and build tool for
any parsing-related issue, including production-quality compiler
construction and the implementation of domains specific languages.

UniCC unions an integrated generator for lexical analyzers and a
powerful LALR(1) parser generator into one software solution. UniCC
interfaces a rich, extendable and innovative EBNF-based grammar
definition language, which gives any compiler-developer's task much more
comfort and simplicity in implementing parsers than ever before.

It comes with useful features for both grammar prototyping and design,
parser optimization, semantic augmentation and parser programming.
Lexical symbols can be directly defined within productions, right-hand
side items can be referenced by meaningful names within semantic
actions, instead of only their offsets. Features like virtual- and
embedded-productions finally help to rapidly build-up iterative and
optional grammatical structures.

Standard features like automatic conflict resolution, terminal and
production precedence association, state compression as well as parser
trace and behavior modification trough semantic actions round up the
whole system.

UniCC is technically a target language independent parser generator,
which means that it is not bound to a special programming language.
Currently, only support of the C programming language is given due the
UniCC Standard C Parser Template. More standard templates for other
languages like C++ and Java will be developed and released in future by
Phorward Software Technologies, but are not available for now; Any help
and support on this area is appreciated.

UniCC has been developed since 2006 and has its origin at Phorward
Software Technologies and is initially written and maintained by its
1985 born core developer, Jan Max Meyer. Phorward Software Technologies
is a software company from Dortmund, Germany, which focuses its business
on compiler construction, scripting languages and software development
tools, both in the area of open source and proprietary solutions.

This document should serve as a quick reference note on how to use UniCC
and set up its environment. There is also additional documentation in
form of a User's Manual available, which is included into the binary
packages of UniCC and can be obtained from the Phorward Software
Technologies website.

Please check out <http://unicc.phorward-software.com/> from time to time
to get the latest news, documentation, updates and support on the UniCC
LALR(1) Parser Generator.

FEATURES
========

The UniCC LALR(1) Parser Generator features the following, unique tools
and possibilities.

-   A powerful and inovative BNF-based grammar definition language
-   Full Unicode support
-   Build-in lexical analyzer generator
-   Grammar prototyping features
-   Virtual productions
-   Anonymous nonterminals
-   Semantically determined symbols
-   Two parser construction modes allow the use of different algorithmic
    approaches relating the whitespace handling
-   Target-language independent parser development
-   Template-based program-module generator and XML-based parser
    description file generator
-   Platform-independent (console-based)
-   Standard LALR(1) conflict resolution
-   Supporting the C programming language via the UniCC Standard C
    Parser Template, providing many useful features like integrated
    Syntax Tree Generator and Error Recovery

ENVIRONMENT SETUP
=================

To get UniCC work properly, the **unicc** executable must be in the
PATH. It is also required to set an environment variable UNICC\_TPLDIR
that directs to a directory holding the UniCC target language templates.
If UNICC\_TPLDIR is not set, UniCC will automatically check for
templates in \$prefix/share/unicc/tlt on Linux/Unix.

COMMAND-LINE OPTIONS
====================

The UniCC command-line interface supports various, combinable options to
invoke, modify and specialize the parser generation process, or to
trigger further tasks.

-a, --all-warnings

> Runs UniCC to print all warnings that come up with the grammar. UniCC
> normaly supresses some warning messages that raise up during the parse
> table constructions according to their importance.

-b *NAME*, --basename *NAME*

> Defines the specified basename *NAME* to be used for the output
> file(s) instead of the one derived by the \#prefix-directive or by the
> name of the input filename. This basename is used for all output files
> if the provided parser template causes the construction of multiple
> files.

-G, --grammar

> Dumps an overview of the finally constructred grammar to stderr, right
> before the parse-tables are generated.

-h, --help

> Prints a short overview about the command-line options and exists.

-n, --no-opt

> Disables state optimization; By default, the resulting LALR(1) parse
> states are optimized during table construction by introducing a
> special SHIFT\_REDUCE action which combines a shift and reduction,
> which is possible when the last symbol of a production is shifted.
> Standard LALR(1) parsers only support SHIFT or REDUCE, not both
> operations at the same time. When this option is used, UniCC produces
> about 20-30% more LALR(1) states.

-P, --production

> Dumps an overview about the finally produced productions and their
> semantic actions.

-s, --stats

> Prints a statistics message to stderr when parser generation has
> entirely been finished. This will automatically switched on when using
> the verbose option.

-S, --states

> Dumps the generated LALR(1) states that had been generated during the
> parse table generation process.

-t, --stdout

> Print all code generator output to stdout instead as files.

-T, --symbols

> Dumps an overview of all used symbols.

-v, --verbose

> Prints process messages about the specific tasks during parser
> generation process. Automatically switches on the stats option for
> statistics output.

-V, --version

> Prints copyright and version information and exits.

-w, --warnings

> Print relevant warnings.

-x, --xml

> Triggers UniCC to run the parser description file generator
> additionally to the program module generator. The parser description
> file generator outputs an XML-based parser representation of the
> generated parse tables, which can be used by third-party code
> generators or grammar analsys and debugging tools.

-X, --XML

> Triggers UniCC to only run the parser description file generator
> without running the program-module generator.

Errors and warnings are printed to STDERR, any other kind of output to
STDOUT.

BUILDING UNICC FROM SOURCE
==========================

UniCC is a software that was entirely established and developed on top
of the Phorward Toolkit.

The Phorward Toolkit and its library *libphorward* provide many useful
functions for general purpose and extended software-development tasks,
including standard data structures, a system-independent interface,
extending data types and regular expression management functions,
required by UniCC to construct the lexical analyzers.

The Phorward Toolkit is released under the BSD License. More information
can be obtained from the official product website at
<http://phorward-software.com.>

Before UniCC can be built, ensure that the Phorward Toolkit is installed
in its latest version.

Getting the latest version is simple using the Mercurial SCM with

    git clone https://github.com/phorward/phorward.git

then, change into the cloned directory and run

    ./configure
    make
    make install

After that, clone the following repositories. They provide the UniCC
Parser Generator and XPL, a demonstration of a tiny programming language
implementation written with UniCC.

    git clone https://github.com/phorward/unicc.git
    git clone https://github.com/phorward/xpl.git

Optionally, if hacking the UniCC Standard C Parser Template is wanted,
clone

    git clone https://github.com/phorward/Cparser.git

also.

Change into the directory `unicc` and, again run

    ./configure
    make
    make install

After UniCC was successfully built and installed, `xpl` can be compiled
out of the box without any configuration script.

If the UniCC bootstrapping toolchain is wanted, configure UniCC with

    ./configure --with-bootstrap

this will bootstrap the UniCC grammar parser with multiple generation
states.

When bootstraping toolchain is enabled, it is additionally required to
install the min\_lalr1 parser generator. This program can be obtained
with

    git clone https://github.com/phorward/min_lalr1.git

AUTHOR
======

The UniCC LALR(1) Parser Generator and all subsequent repositories and
tools is written and maintained by Jan Max Meyer, Phorward Software
Technologies.

Some other projects by the author are:

-   *pynetree* (http://pynetree.org): A light-weight parsing toolkit
    written in pure Python.
-   *phorward* (http://phorward.phorward-software.com): A free toolkit
    for parser development, lexical analysis, regular expressions and
    more.
-   *JS/CC* (http://jscc.brobston.com): The JavaScript parser generator.

COPYRIGHT
=========

Copyright (C) 2006-2017 by Phorward Software Technologies, Jan Max
Meyer.

You may use, modify and distribute this software under the terms and
conditions of the 3-clause BSD license. The full license terms can be
obtained from the file LICENSE.

