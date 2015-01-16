//
//  AbstractInvocation.h
//  Pepper
//
//  Created by Dave Meehan on 16/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_AbstractInvocation_h
#define Pepper_AbstractInvocation_h

#include "Befores.h"
#include "Steps.h"
#include "Formatter.h"

namespace Pepper {

    class AbstractInvocation : public Gherkin::NodeVisitor {

    public:

        AbstractInvocation(Befores const &befores,
                           Steps const &steps,
                           std::shared_ptr<Formatter> const &formatter)
        :
        _befores(befores),
        _steps(steps),
        _formatter(formatter)
        {}

        void visit(Gherkin::Node &node) override { }
        void visit(Gherkin::Feature &node) override { }
        void visit(Gherkin::Scenario &node) override { }
        void visit(Gherkin::Step &step) override { }

        Befores const &befores() const {
            return _befores;
        }

        Steps const &steps() const {
            return _steps;
        }

        std::shared_ptr<Formatter> const &formatter() const {
            return _formatter;
        }

    private:

        Befores                         _befores;
        Steps                           _steps;
        std::shared_ptr<Formatter>      _formatter;

    };

}

#endif
