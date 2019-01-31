//
//  LibAnalyser.cpp
//  LibAnalyser
//
//  Created by David Thomas on 01/2019.
//  Copyright © 2019 David Thomas. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "LibAnalyser.hpp"

enum PARSELINE_RESULT
{
    SUCCESS,
    IGNORE,
    OUT_OF_RANGE,
    PARSE_ERROR
};

/**
 * Parse a single line of input.
 *
 * The line is expected to hold a single integer. Deviances from that will
 * result in PARSE_ERROR being returned. Out-of-range values will result in
 * OUT_OF_RANGE being returned. Empty lines will return IGNORE. Successfully
 * read values will be returned in pnum. pnum is zeroed in non-success cases.
 *
 * \param line  The line to parse.
 * \param pnum  Parsed number.
 *
 * \return Error indication, as above.
 */
static PARSELINE_RESULT parse_line(std::string& line, long long& pnum)
{
    char      *endptr;
    long long  num;

    pnum = 0;

    // skip empty lines
    if (line.length() == 0)
        return IGNORE;

    // parse the number
    errno = 0;
    num = std::strtoll(line.c_str(), &endptr, 10);

    // fault out of range values
    if (errno != 0 || num < LLONG_MIN || num > LLONG_MAX)
        return OUT_OF_RANGE;

    // permit trailing whitespace
    while (isspace(*endptr))
        endptr++;

    // fault if any unidentified characters remain after parsing
    if (*endptr != '\0')
        return PARSE_ERROR;

    pnum = num;

    return SUCCESS;
}

int analyse(const char *input, const char *output)
{
    bool failure = false;

    std::ifstream instream(input);
    if (!instream.is_open())
    {
        std::cerr << "Input file could not be opened" << std::endl;
        return -1;
    }

    int seen = 0;
    long long sum = 0;

    // loop until we hit EOF
    for (;;)
    {
        std::string line;
        long long   num;
        int         result;

        // attempt the getline() before testing for failure conditions
        std::getline(instream, line);
        if (!instream.good())
        {
            if (!instream.eof())
                failure = true;
            break;
        }

        result = parse_line(line, num);
        if (result == IGNORE)
        {
            continue;
        }
        else if (result != SUCCESS)
        {
            std::cerr << "Parse error for \'" << line << "\'" << std::endl;
            failure = true;
            break;
        }

        seen++;
        sum += num;
    }
    instream.close();

    if (failure)
        return -1;

    std::ofstream outstream(output);
    if (!outstream.is_open())
    {
        instream.close();
        std::cerr << "Output file could not be opened" << std::endl;
        return -1;
    }

    outstream << "count = " << seen << std::endl;
    outstream << "sum = " << sum << std::endl;
    if (seen > 0)
        outstream << "average = " << (double) sum / seen << std::endl;
    else
        // avoid division by zero
        outstream << "average = (undefined)" << std::endl;
    outstream.close();

    return 0;
}
