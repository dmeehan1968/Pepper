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
#include "Counters.h"

namespace Pepper {

    class FeatureInvocation : public AbstractInvocation {

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

            _scenarioCounters.pending() = node.children().size();

            for (auto &child : node.children()) {

                ScenarioInvocation invocation(befores(), steps(), formatter(), feature);

                child->accept(invocation);

                _scenarioCounters.pending()--;

                if (invocation.pending()
                    || invocation.undefined()
                    || invocation.skipped()) {

                    _scenarioCounters.pending()++;

                } else if (invocation.failures()) {

                    _scenarioCounters.failures()++;

                } else {

                    _scenarioCounters.passed()++;

                }

                _stepCounters.passed() += invocation.passed();
                _stepCounters.pending() += invocation.pending();
                _stepCounters.undefined() += invocation.undefined();
                _stepCounters.skipped() += invocation.skipped();
                _stepCounters.failures() += invocation.failures();

            }
            
            formatter()->after(*this);

        }

        Counters const &scenarioCounters() const {
            return _scenarioCounters;
        }

        Counters const &stepCounters() const {
            return _stepCounters;
        }

    private:

        Counters        _scenarioCounters;
        Counters        _stepCounters;

    };

}

#endif
