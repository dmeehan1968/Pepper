//
//  SpecRunner.h
//  Pepper
//
//  Created by Dave Meehan on 14/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_SpecRunner_h
#define Pepper_SpecRunner_h

#include "Step.h"
#include "Before.h"
#include "Feature.h"

#include <Gherkin-Cpp/NodeVisitor.h> 
#include <Gherkin-Cpp/Node.h>
#include <Gherkin-Cpp/Feature.h>
#include <Gherkin-Cpp/Scenario.h>
#include <Gherkin-Cpp/Step.h>

namespace Pepper {

    class SpecRunner : public Gherkin::NodeVisitor {

    public:

        void add(std::shared_ptr<Step> const &step) {

            _steps.emplace_back(step);

        }

        void add(std::shared_ptr<Before> const &before) {

            _befores.emplace_back(before);

        }

        void visit(Gherkin::Node &node) {

            std::cout << node << std::endl;

            doChildren(node);

        }

        void visit(Gherkin::Feature &node) {

            std::cout << node << std::endl;

            _currentFeature = std::make_shared<Feature>();

            doBefores(node);

            doChildren(node);

            _currentFeature.reset();

        }

        void visit(Gherkin::Scenario &node) {

            std::cout << node << std::endl;

            doBefores(node);

            doChildren(node);

        }

        void visit(Gherkin::Step &node) {

            std::cout << node << std::endl;

            doBefores(node);

            for (auto &step : _steps) {

                auto args = step->accepts(node.name());

                if (args) {

                    step->setWorld(_currentFeature->world<World>());
                    
                    (*step)(*args);

                }
            }

            doChildren(node);


        }

    protected:

        void doBefores(Gherkin::Node &node) {

            for (auto &before : _befores) {

                auto args = before->accept(node.name());

                if (args) {

                    (*before)(*_currentFeature, *args);

                }
            }
        }

        void doChildren(Gherkin::Node &node) {

            for (auto &child : node.children()) {

                child->accept(*this);
                
            }

        }

    private:

        std::list<std::shared_ptr<Step>>    _steps;
        std::list<std::shared_ptr<Before>>  _befores;

        std::shared_ptr<Feature>            _currentFeature;
        
    };

}

#endif
