//
//  Pepper.cpp
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#include "Pepper.h"
#include "Args.h"
#include "Before.h"
#include "Step.h"
#include "World.h"

namespace Zing { namespace Pepper {

    void Pepper::add(std::shared_ptr<StepDefinitions::Step> const &step) {

        _steps.emplace_back(step);

    }

    void Pepper::before(std::shared_ptr<StepDefinitions::Before> const &before) {

        _befores.emplace_back(before);

    }

    void Pepper::invokeBeforesThatMatch(StepDefinitions::Feature &feature, std::string const &name) {

        std::find_if(_befores.begin(), _befores.end(), [&](std::shared_ptr<StepDefinitions::Before> const &before) {

            std::unique_ptr<Zing::App::Args> args;

            if ((bool)(args = before->accepts(name))) {

                (*before)(feature, *args);
                return true;

            }

            return false;

        });

    }

    void Pepper::invokeStepsThatMatch(StepDefinitions::Feature &feature, std::string const &name) {

        std::find_if(_steps.begin(), _steps.end(), [&](std::shared_ptr<StepDefinitions::Step> const &step) {

            std::unique_ptr<Zing::App::Args> args;
            
            if ((bool)(args = step->accepts(name))) {
                
                step->setWorld(feature.world<StepDefinitions::World>());
                
                (*step)(*args);
                return true;
                
            }
            
            return false;
            
        });
        
    }

} }