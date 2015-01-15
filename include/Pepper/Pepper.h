//
//  Pepper.h
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef __DelegateTest__Pepper__
#define __DelegateTest__Pepper__

#include <Gherkin-Cpp/GherkinParser.h>

#include <iostream>

namespace Pepper {

    class Step;
    class Before;

    class Pepper {

    public:

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

    };

}

#endif /* defined(__DelegateTest__Pepper__) */
