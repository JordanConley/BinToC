# BINTOC

## Description
Creates a C source file and matching header file for a binary dump.

By default, takes input from stdin and produces valid C output to stdout. 

## Arguments
Arguments to the program are given in key=value pairs.

Possible arguments are:

| Command | Description |
| --- | --- |
| infile | Specifies input file. If ommitted, defaults to stdin |
| outfile | Specifes output file names. Header and source file names are
            based on this argument. For instance with outfile=abc, abc.c and
            abc.h are produced. If omitted, the C file defaults to stdout and no
            header is produced. |
| var | Specifies variable name. If omitted, the default is "data" |

