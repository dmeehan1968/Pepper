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

namespace Pepper {

    class ScenarioInvocation : public AbstractInvocation {

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

            formatter()->before(node);

            befores().accept(node.name(), *_feature);

            for (auto &child : node.children()) {

                StepInvocation invocation(befores(), steps(), formatter(), _feature);

                child->accept(invocation);

            }

            formatter()->after(node);
            
        }
        
    private:
        
        std::shared_ptr<Feature>    _feature;
        
    };

}

#endif
