//
//  Before.cpp
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#include "Before.h"
#include <ZingCpp/Args.h>

namespace Pepper {

    Before::Before(std::string const &expr, std::regex::flag_type flags)
    :
        _expr(expr, flags)
    {}

    Before::~Before() {}

    std::unique_ptr<Zing::Args> Before::accept(std::string const &string) {

        std::smatch matches;

        if (std::regex_match(string, matches, _expr)) {

            auto args = std::unique_ptr<Zing::Args>(new Zing::Args());

            if (matches.size() > 1) {

                std::for_each(matches.begin()+1, matches.end(), [&](decltype(*matches.begin()) const &match) {

                    args->push_back(match.str());

                });

            }

            return args;

        }

        return {};

    }

}
