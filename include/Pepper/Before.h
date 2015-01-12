//
//  Before.h
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef __DelegateTest__Before__
#define __DelegateTest__Before__

#include "../../App/Args.h"
#include "Feature.h"

#include <string>
#include <memory>
#include <regex>

namespace Zing { namespace Pepper { namespace StepDefinitions {

    class Before {

    public:

        Before(std::string const &expr,
               std::regex::flag_type flags = std::regex::ECMAScript);

        virtual ~Before();

        std::unique_ptr<Zing::App::Args> accepts(std::string const &string);
        
        virtual void operator()(Feature &feature, Zing::App::Args &args) = 0;
        
    private:
        
        std::regex      _expr;
        
    };

} } }

#endif /* defined(__DelegateTest__Before__) */
