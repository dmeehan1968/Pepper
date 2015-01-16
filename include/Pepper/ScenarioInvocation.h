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
        _feature(feature),
        _passed(0),
        _pending(0),
        _undefined(0),
        _skipped(0),
        _failures(0)
        {}

        void visit(Gherkin::Scenario &node) override {

            setNode(node);
            
            formatter()->before(*this);

            _pending = node.children().size();

            befores().accept(node.name(), *_feature);

            for (auto &child : node.children()) {

                StepInvocation invocation(befores(), steps(), formatter(), _feature);

                child->accept(invocation);

                _pending--;
                switch (invocation.state()) {
                    case InvocationState::Pending:
                        _pending++;
                        break;

                    case InvocationState::Undefined:
                        _undefined++;
                        break;

                    case InvocationState::Skipped:
                        _skipped++;
                        break;

                    case InvocationState::Failed:
                        _failures++;
                        break;

                    case InvocationState::Passed:
                        _passed++;
                        break;

                    default:
                        throw std::runtime_error("Illegal Invocation State");
                }

            }

            formatter()->after(*this);
            
        }

        size_t passed() const {
            return _passed;
        }

        size_t pending() const {
            return _pending;
        }

        size_t undefined() const {
            return _undefined;
        }

        size_t skipped() const {
            return _skipped;
        }

        size_t failures() const {
            return _failures;
        }
        
    private:
        
        std::shared_ptr<Feature>    _feature;
        size_t                      _passed;
        size_t                      _pending;
        size_t                      _undefined;
        size_t                      _skipped;
        size_t                      _failures;

    };

}

#endif
