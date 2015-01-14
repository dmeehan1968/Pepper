//
//  Step.cpp
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#include "Step.h"
#include <ZingCpp/Args.h>

namespace Zing { namespace Pepper { namespace StepDefinitions {

    Step::Step(std::string const &expr, std::regex::flag_type flags)
    :
        _expr(expr, flags)
    { }

    std::unique_ptr<App::Args> Step::accepts(std::string const &string) const {

        std::smatch matches;

        if (std::regex_match(string, matches, _expr)) {

            auto args = std::unique_ptr<App::Args>(new App::Args());

            if (matches.size() > 1) {

                std::for_each(matches.begin()+1, matches.end(), [&](decltype(*matches.begin()) const &match) {

                    args->push_back(match.str());

                });

            }

            return args;

        }

        return {};

    }

    void Step::setWorld(std::shared_ptr<World> const &world) {
        _world = world;
    }

} } }