//
//  main.cpp
//  AnalyserFE
//
//  Created by David Thomas on 01/2019.
//  Copyright © 2019 David Thomas. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include "../../LibAnalyser/LibAnalyser/LibAnalyser.hpp"

static void usage(const char *progname)
{
    std::cerr << "Usage: " << progname << " INFILE OUTFILE" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[])
{
    const char  *progname = NULL;
    const char  *input    = NULL;
    const char  *output   = NULL;
    int          rc;

    progname = argv[0];
    argc--;
    argv++;

    if (argc < 2)
        usage(progname);

    for (; argc > 0; argc--, argv++)
    {
        if (!input)
            input = argv[0];
        else if (!output)
            output = argv[0];
        else
            usage(progname);
    }

    rc = analyse(input, output);
    if (rc)
    {
        std::cerr << progname << ": analyse() failure (" << rc << ")" << std::endl;
        goto failure;
    }

    exit(EXIT_SUCCESS);


failure:
    exit(EXIT_FAILURE);
}


