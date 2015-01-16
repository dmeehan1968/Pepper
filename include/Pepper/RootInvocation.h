//
//  RootInvocation.h
//  Pepper
//
//  Created by Dave Meehan on 16/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_RootInvocation_h
#define Pepper_RootInvocation_h

#include "FeatureInvocation.h"

namespace Pepper {

    class RootInvocation : public AbstractInvocation {

    public:

        RootInvocation(Befores const &befores,
                       Steps const &steps,
                       std::shared_ptr<Formatter> const &formatter)
        :
        AbstractInvocation(befores, steps, formatter)
        {}

        void visit(Gherkin::Node &node) override {

            for (auto &child : node.children()) {

                FeatureInvocation invocation(befores(), steps(), formatter());

                child->accept(invocation);

            }
            
        }
        
    };

}

#endif
