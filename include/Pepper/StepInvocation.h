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

namespace Pepper {

    class StepInvocation : public AbstractInvocation {

    public:

        StepInvocation(Befores const &befores,
                       Steps const &steps,
                       std::shared_ptr<Formatter> const &formatter,
                       std::shared_ptr<Feature> const &feature)
        :
        AbstractInvocation(befores, steps, formatter),
        _feature(feature)
        {}

        void visit(Gherkin::Step &node) override {

            formatter()->before(node);

            befores().accept(node.name(), *_feature);

            steps().accept(node.name(), _feature);

            formatter()->after(node);
            
            // TODO
            
        }
        
    private:
        
        std::shared_ptr<Feature>    _feature;
        
    };
    
}

#endif
