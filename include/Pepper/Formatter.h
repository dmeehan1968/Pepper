//
//  Formatter.h
//  Pepper
//
//  Created by Dave Meehan on 15/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_Formatter_h
#define Pepper_Formatter_h

namespace Pepper {

    class RootInvocation;
    class FeatureInvocation;
    class ScenarioInvocation;
    class StepInvocation;
    
    class Formatter {

    public:

        virtual ~Formatter() = 0;

        virtual void before(RootInvocation const &invocation) {}
        virtual void after(RootInvocation const &invocation) {}

        virtual void before(FeatureInvocation const &invocation) {}
        virtual void after(FeatureInvocation const &invocation) {}

        virtual void before(ScenarioInvocation const &invocation) {}
        virtual void after(ScenarioInvocation const &invocation) {}

        virtual void before(StepInvocation const &invocation) {}
        virtual void after(StepInvocation const &invocation) {}

    };
    
    inline Formatter::~Formatter() {}
    
}

#endif
