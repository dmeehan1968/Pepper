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
#include "Statistic.h"
#include "Status.h"
#include "Step.h"
#include "Steps.h"

#include <Gherkin-Cpp/NodeVisitor.h> 
#include <Gherkin-Cpp/Node.h>
#include <Gherkin-Cpp/Feature.h>
#include <Gherkin-Cpp/Scenario.h>
#include <Gherkin-Cpp/Step.h>

namespace Pepper {

    class SpecRunner : public Gherkin::NodeVisitor {

    public:

        SpecRunner(std::shared_ptr<Formatter> const &formatter)
        :
        _formatter(formatter)
        {}

        void add(std::shared_ptr<Step> const &step) {

            _steps.push_back(step);

        }

        void add(std::shared_ptr<Before> const &before) {

            _befores.push_back(before);

        }

        void visit(Gherkin::Node &node) {

            doChildren(node);

        }

        void visit(Gherkin::Feature &node) {

            _formatter->before(node);

            _currentFeature = std::make_shared<Feature>();

            _befores.accept(node.name(), *_currentFeature);

            doChildren(node);

            _currentFeature.reset();

            _formatter->after(node);

        }

        void visit(Gherkin::Scenario &node) {

            _formatter->before(node);

            _befores.accept(node.name(), *_currentFeature);

            _scenarioStat.clear();
            _scenarioStat.total(node.children().size());

            doChildren(node);

            _formatter->after(node, _scenarioStat);

        }

        void visit(Gherkin::Step &node) {

            _formatter->before(node);

            _befores.accept(node.name(), *_currentFeature);

            Status status = Status::Pending;

            try {

                _steps.accept(node.name(), _currentFeature);

                status = Status::Success;

            } catch (std::exception &e) {

                status = Status::Failed;
                _scenarioStat.exception(std::make_shared<std::exception>(e));

            }

            _formatter->after(node, status);

        }

    protected:

        void doChildren(Gherkin::Node &node) {

            for (auto &child : node.children()) {

                child->accept(*this);

            }

        }

    private:

        std::shared_ptr<Formatter>          _formatter;

        Steps                               _steps;
        Befores                             _befores;

        std::shared_ptr<Feature>            _currentFeature;
        Statistic                           _scenarioStat;

    };

}

#endif
