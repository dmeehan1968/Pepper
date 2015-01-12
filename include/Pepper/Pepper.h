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

            std::unique_ptr<StepDefinitions::Feature> feature;

            std::for_each(begin, end, [&](decltype(*begin) const &string) {

                std::regex expr("^\\s*(feature:|scenario:|given|when|then|and)\\s*(.*)\\s*$", std::regex::icase | std::regex::ECMAScript);
                std::smatch matches;

                if (std::regex_match(string, matches, expr)) {

                    auto keyword = matches[1].str();
                    std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

                    if (keyword == "feature:") {

                        feature = std::unique_ptr<StepDefinitions::Feature>(new StepDefinitions::Feature());

                    }

                    std::cout << matches.str() << std::endl;

                    invokeBeforesThatMatch(*feature, matches[2]);

                    std::list<std::string> stepKeywords = { "given", "when", "then", "and", "but" };

                    if (std::find(stepKeywords.begin(), stepKeywords.end(), keyword) != stepKeywords.end()) {

                        invokeStepsThatMatch(*feature, matches[2]);

                    }

                }

            });
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
