// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)


// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:


// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>

#include "dsp/FilterbankCPU.hpp"
#include "dsp/Filterbank.h"
#include "dsp/FilterbankConfig.h"
#include "dsp/Memory.h"

#if HAVE_CUDA
#include "dsp/MemoryCUDA.h"
#include <cuda_runtime.h>
#endif

#include "gtest/gtest.h"

using namespace std;

namespace {

ostream cerrStream(NULL);

ostream& isVerbose(ostream &stream)
{
    return (dsp::Filterbank::verbose) ? cerr : stream;
}

TEST(FilterbankSetGetChan, Positive) {

	dsp::Operation::verbose = false;
	dsp::Filterbank::Config filterbankConfig;
	dsp::Filterbank* filterbank = filterbankConfig.create();

	// given
	unsigned nchan = 128;
	
	// when
	filterbank->set_nchan(nchan);

	// then
	// ASSERT_* : Fatal Assertion
	ASSERT_EQ(filterbank->get_nchan(), nchan);
	cerrStream << isVerbose << filterbank->get_nchan() << std::endl;
}

TEST(FilterbankSetGetChan, Negative) {

	dsp::Operation::verbose = false;
	dsp::Filterbank::Config filterbankConfig;
	dsp::Filterbank* filterbank = filterbankConfig.create();
	
	// given
	unsigned nchan = -128;
	
	// when
	filterbank->set_nchan(nchan);
	
	// then
	ASSERT_EQ(filterbank->get_nchan(), nchan);
	cerrStream << isVerbose << nchan << " vs "<< filterbank->get_nchan() << std::endl;
}

TEST(FilterbankSetGetFrequencyResolution, Positive) {

	dsp::Operation::verbose = false;
	dsp::Filterbank::Config filterbankConfig;
	dsp::Filterbank* filterbank = filterbankConfig.create();

	// given
	unsigned frequencyResolution = 1024;
	
	// when
	filterbank->set_freq_res(frequencyResolution);

	// then
	// ASSERT_* : Fatal Assertion
	ASSERT_EQ(filterbank->get_freq_res(), frequencyResolution);
	cerrStream << isVerbose << frequencyResolution << " vs "<< filterbank->get_freq_res() << std::endl;
}

TEST(FilterbankSetGetFrequencyResolution, Negative) {

	dsp::Operation::verbose = false;
	dsp::Filterbank::Config filterbankConfig;
	dsp::Filterbank filterbank; // = filterbankConfig.create();

	// give
	unsigned frequencyResolution = -1024;
	
	// when
	filterbank.set_freq_res(frequencyResolution);
	
	// then
	ASSERT_EQ(filterbank.get_freq_res(), frequencyResolution);
	cerrStream << isVerbose << frequencyResolution << " vs "<< filterbank.get_freq_res() << std::endl;
}


TEST(IsPrimeTestFilterbank, Positive) {
	FilterbankEngineCPU filterbankEngineCPU;

	// EXPECT_* : Nonfatal assertion
    EXPECT_FALSE(filterbankEngineCPU.IsPrime(4));
    EXPECT_TRUE(filterbankEngineCPU.IsPrime(5));
}

}  // namespace

