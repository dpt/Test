//
//  LibAnalyser.hpp
//  LibAnalyser
//
//  Created by David Thomas on 01/2019.
//  Copyright © 2019 David Thomas. All rights reserved.
//

#ifndef LibAnalyser_hpp
#define LibAnalyser_hpp

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Analyse an input file.
 *
 * Analyse a file consisting of whole numbers, one per line, and output a
 * new file with the count of numbers read, the sum of the numbers and the
 * average of the numbers.
 *
 * \param[in] input   Input filename.
 * \param[in] output  Output filename.
 *
 * \return 0 if the operation was successful, negative otherwise.
 */
int analyse(const char *input, const char *output);

#ifdef __cplusplus
}
#endif

#endif /* LibAnalyser_hpp */
