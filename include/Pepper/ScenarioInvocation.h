//
//  ScenarioInvocation.h
//  Pepper
//
//  Created by Dave Meehan on 16/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_ScenarioInvocation_h
#define Pepper_ScenarioInvocation_h

#include "StepInvocation.h"
#include "Counters.h"

namespace Pepper {

    class ScenarioInvocation : public AbstractInvocation, public Counters {

    public:

        ScenarioInvocation(Befores const &befores,
                           Steps const &steps,
                           std::shared_ptr<Formatter> const &formatter,
                           std::shared_ptr<Feature> const &feature)
        :
        AbstractInvocation(befores, steps, formatter),
        _feature(feature)
        {}

        void visit(Gherkin::Scenario &node) override {

            setNode(node);
            
            formatter()->before(*this);

            pending() = node.children().size();

            befores().accept(node.name(), *_feature);

            bool skip = false;

            for (auto &child : node.children()) {

                StepInvocation invocation(befores(), steps(), formatter(), _feature, skip);

                child->accept(invocation);

                pending()--;
                switch (invocation.state()) {
                    case InvocationState::Pending:
                        pending()++;
                        break;

                    case InvocationState::Undefined:
                        undefined()++;
                        skip = true;
                        break;

                    case InvocationState::Skipped:
                        skipped()++;
                        break;

                    case InvocationState::Failed:
                        failures()++;
                        skip = true;
                        break;

                    case InvocationState::Passed:
                        passed()++;
                        break;

                    default:
                        throw std::runtime_error("Illegal Invocation State");
                }

            }

            formatter()->after(*this);
            
        }

    private:
        
        std::shared_ptr<Feature>    _feature;

    };

}

#endif
