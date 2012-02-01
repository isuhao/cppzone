/*
 *  Copyright (c) 2011 Evgeny Proydakov <lord.tiran@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include <iostream>
#include <cstring>

#include <benchmark.h>

#include "operations_with_numbers.h"

typedef double data_type;
typedef int natural_data_type;
typedef int index_type;

typedef data_type (*prt_fun_1)(index_type);
void test_fun(const std::string& name, const std::string& type, prt_fun_1 fun, index_type n);

typedef natural_data_type (*prt_fun_2)(natural_data_type, natural_data_type);
void test_largest_common_divisor(const std::string& name, prt_fun_2 fun, natural_data_type a, natural_data_type b);

void skip_line()
{
    std::cout << std::endl;
}

int main( int argc, char *argv[] )
{
    (void)argc;
    (void)argv;
    
    // test fibonacci
    test_fun("RECURSIVE", "FIBONACCI", fibonacci_recursive, 35);
    test_fun("MATRIX", "FIBONACCI", fibonacci_matrix, 35);
    
    skip_line();
    
    // test factorial
    test_fun("RECURSIVE", "FACTORIAL", factorial_recursive, 15);
    test_fun("CYCLIC",  "FACTORIAL", factorial_cyclic, 15);
    test_fun("STIRLING",  "FACTORIAL", factorial_stirling, 15);
    
    test_fun("SUM DIVIDED BY THE FACTORIAL", "", sum_divided_by_the_factorial, 15);
    
    skip_line();
    
    // test lowest common divisor
    test_largest_common_divisor("SIMPLE", largest_common_divisor, 90, 100);
    test_largest_common_divisor("EUCLID", largest_common_divisor_euclid, 100, 90);
    test_largest_common_divisor("MOD EUCLID", largest_common_divisor_modified_euclid, 90, 100);
    
    return 0;
}

void test_fun(const std::string& name, const std::string& type, prt_fun_1 fun, index_type n)
{
    data_type current_n = 0;
    benchmark::benchmark current_benchmark;
    current_benchmark.start(); {
        current_n = fun(n);
    }
    current_benchmark.stop();
    std::cout << "BENCHMARK  " << name << "  " << type << "  num  " << n <<  ":  " << current_n
              << "  TIME:  " << current_benchmark.get_last_interval() << std::endl;
}

void test_largest_common_divisor(const std::string& name, prt_fun_2 fun, natural_data_type a, natural_data_type b)
{
    data_type current_divisor = fun(a, b);
    std::cout << "Largest common divisor " << name << "  from:  " 
              << a << "  and  " << b <<  "  -  " << current_divisor << std::endl;    
}