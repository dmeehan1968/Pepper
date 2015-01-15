//
//  Steps.h
//  Pepper
//
//  Created by Dave Meehan on 15/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_Steps_h
#define Pepper_Steps_h

#include "Step.h"
#include "Feature.h"

#include <list>
#include <exception>

namespace Pepper {

    class World;

    class Steps {

    public:

        void push_back(std::shared_ptr<Step> const &step) {
            _steps.push_back(step);
        }

        void accept(std::string const &name,
                    std::shared_ptr<Feature> const &feature) {

            for (auto &step : _steps) {

                auto args = step->accept(name);

                if (args) {

                    step->setWorld(feature->world<World>());

                    (*step)(*args);
                    return;
                }
            }

            throw std::runtime_error("Undefined");
            
        }
        
    private:
        
        std::list<std::shared_ptr<Step>> _steps;
        
    };

}

#endif
