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

    class Statistic;
    enum class Status;

    class Formatter {

    public:

        virtual ~Formatter() = 0;

        virtual void before(Gherkin::Feature const &feature) {}
        virtual void after(Gherkin::Feature const &feature) {}

        virtual void before(Gherkin::Scenario const &scenario) {}
        virtual void after(Gherkin::Scenario const &scenario) {}

        virtual void before(Gherkin::Step const &step) {}
        virtual void after(Gherkin::Step const &step) {}

    };
    
    inline Formatter::~Formatter() {}
    
}

#endif
