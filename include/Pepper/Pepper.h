//
//  Pepper.h
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef __DelegateTest__Pepper__
#define __DelegateTest__Pepper__

#include <memory>
#include <algorithm>
#include <regex>
#include <iostream>
#include <list>

#include "Feature.h"

#include <Gherkin/NodeVisitor.h>
#include <Gherkin/Node.h>
#include <Gherkin/Feature.h>
#include <Gherkin/Scenario.h>
#include <Gherkin/Step.h>
#include <Gherkin/Printer.h>
#include <Gherkin/NodeFactory.h>
#include <Gherkin/ParserNodeException.h>
#include <Gherkin/AbstractParser.h>
#include <Gherkin/ScenarioParser.h>
#include <Gherkin/FeatureParser.h>
#include <Gherkin/GherkinParser.h>

namespace Zing { namespace Pepper {

    namespace StepDefinitions {

        class Step;
        class Before;

    }

    class Pepper {

    public:

        void add(std::shared_ptr<StepDefinitions::Step> const &step);

        void before(std::shared_ptr<StepDefinitions::Before> const &before);

        template <typename InputIterator>
        void parse(InputIterator begin, InputIterator const end) {

            try {

                using namespace Gherkin;

                auto root = std::make_shared<Node>();

                GherkinParser<decltype(begin)>(begin, end, root).parse();

                Printer printer;
                root->accept(printer);

            } catch (std::exception &e) {
                
                std::cout << "Exception: " << e.what() << std::endl;
                
            }
            

        }

    protected:

        void invokeBeforesThatMatch(StepDefinitions::Feature &feature, std::string const &name);

        void invokeStepsThatMatch(StepDefinitions::Feature &feature, std::string const &name);
        
    private:
        
        std::list<std::shared_ptr<StepDefinitions::Step>>        _steps;
        std::list<std::shared_ptr<StepDefinitions::Before>>      _befores;
        
    };

} }

#endif /* defined(__DelegateTest__Pepper__) */
