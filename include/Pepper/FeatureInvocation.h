//
//  FeatureInvocation.h
//  Pepper
//
//  Created by Dave Meehan on 16/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_FeatureInvocation_h
#define Pepper_FeatureInvocation_h

#include "ScenarioInvocation.h"
#include "StepCounters.h"

namespace Pepper {

    class FeatureInvocation : public AbstractInvocation, public StepCounters {

    public:

        FeatureInvocation(Befores const &befores,
                          Steps const &steps,
                          std::shared_ptr<Formatter> const &formatter)
        :
        AbstractInvocation(befores, steps, formatter)
        {}

        void visit(Gherkin::Feature &node) override {

            setNode(node);
            
            formatter()->before(*this);

            auto feature = std::make_shared<Feature>();

            befores().accept(node.name(), *feature);

            for (auto &child : node.children()) {

                ScenarioInvocation invocation(befores(), steps(), formatter(), feature);

                child->accept(invocation);

                passed() += invocation.passed();
                pending() += invocation.pending();
                undefined() += invocation.undefined();
                skipped() += invocation.skipped();
                failures() += invocation.failures();

            }
            
            formatter()->after(*this);
        }

    private:

    };

}

#endif
