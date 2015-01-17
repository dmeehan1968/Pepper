//
//  StepInvocation.h
//  Pepper
//
//  Created by Dave Meehan on 16/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_StepInvocation_h
#define Pepper_StepInvocation_h

#include "AbstractInvocation.h"
#include "InvocationState.h"
#include "InvocationException.h"

namespace Pepper {

    class StepInvocation : public AbstractInvocation {

    public:

        StepInvocation(Befores const &befores,
                       Steps const &steps,
                       std::shared_ptr<Formatter> const &formatter,
                       std::shared_ptr<Feature> const &feature,
                       bool const skip)
        :
        AbstractInvocation(befores, steps, formatter),
        _feature(feature),
        _state(InvocationState::Pending),
        _skip(skip)
        {}

        void visit(Gherkin::Step &node) override {

            setNode(node);

            formatter()->before(*this);

            befores().accept(node.name(), *_feature);

            try {

                if (skip()) {

                    _state = InvocationState::Skipped;

                } else {

                    steps().accept(node.name(), _feature);
                    _state = InvocationState::Passed;
                    
                }

            } catch (InvocationException &e) {

                _state = e.state();
                _exception = std::make_shared<InvocationException>(e);
                
            } catch (std::exception &e) {

                _state = InvocationState::Failed;
                _exception = std::make_shared<InvocationException>(_state, e.what());

            }

            formatter()->after(*this);
            
        }

        InvocationState state() const {
            return _state;
        }

        bool skip() const {
            return _skip;
        }

    private:
        
        std::shared_ptr<Feature>                _feature;
        InvocationState                         _state;
        std::shared_ptr<InvocationException>    _exception;
        bool                                    _skip;

    };
    
}

#endif
