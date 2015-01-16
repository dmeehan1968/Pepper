//
//  SpecRunner.h
//  Pepper
//
//  Created by Dave Meehan on 14/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_SpecRunner_h
#define Pepper_SpecRunner_h

#include "Before.h"
#include "Befores.h"
#include "Feature.h"
#include "Formatter.h"
#include "Step.h"
#include "Steps.h"

#include <Gherkin-Cpp/NodeVisitor.h> 
#include <Gherkin-Cpp/Node.h>
#include <Gherkin-Cpp/Feature.h>
#include <Gherkin-Cpp/Scenario.h>
#include <Gherkin-Cpp/Step.h>

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

    class FeatureInvocation : public AbstractInvocation {

    public:

        FeatureInvocation(Befores const &befores,
                          Steps const &steps,
                          std::shared_ptr<Formatter> const &formatter)
        :
        AbstractInvocation(befores, steps, formatter)
        {}

        void visit(Gherkin::Feature &node) override {

            formatter()->before(node);

            auto feature = std::make_shared<Feature>();

            befores().accept(node.name(), *feature);

            for (auto &child : node.children()) {

                ScenarioInvocation invocation(befores(), steps(), formatter(), feature);

                child->accept(invocation);

            }

            formatter()->after(node);
        }

    };

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
