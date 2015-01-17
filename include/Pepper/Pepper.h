//
//  Pepper.h
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef __DelegateTest__Pepper__
#define __DelegateTest__Pepper__

#include "RootInvocation.h"
#include "Befores.h"
#include "Steps.h"

#include <Gherkin-Cpp/GherkinParser.h>

#include <iostream>

namespace Pepper {

    class Step;
    class Before;

    class Pepper {

    public:

        Pepper(Befores const &befores, Steps const &steps)
        :
        _befores(befores),
        _steps(steps)
        {}

        template <typename InputIterator>
        void run(std::shared_ptr<Formatter> const &formatter, InputIterator begin, InputIterator const end) {

            auto root = parse(begin, end);

            if (root) {
                RootInvocation invocation(_befores, _steps, formatter);
                root->accept(invocation);
            }

        }

    protected:

        template <typename InputIterator>
        std::shared_ptr<Gherkin::Node> parse(InputIterator begin, InputIterator const end) {

            try {

                auto location = std::make_shared<Gherkin::Location>("test.feature");
                auto root = std::make_shared<Gherkin::Node>(*location);

                Gherkin::GherkinParser<decltype(begin)>(begin, end, location, root).parse();

                return root;

            } catch (std::exception &e) {
                
                std::cout << "Exception: " << e.what() << std::endl;
                
            }

            return {};
            
        }

    private:

        Befores     _befores;
        Steps       _steps;


    };

}

#endif /* defined(__DelegateTest__Pepper__) */
