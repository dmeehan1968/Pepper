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

#include <Gherkin-Cpp/GherkinParser.h>
#include <Gherkin-Cpp/Printer.h>

namespace Zing { namespace Pepper {

    class Pepper {

    public:

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

    };

} }

#endif /* defined(__DelegateTest__Pepper__) */
