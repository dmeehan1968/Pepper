//
//  Step.h
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef __DelegateTest__Step__
#define __DelegateTest__Step__

#include "../../App/Args.h"
#include "Step.h"
#include "World.h"

#include <memory>
#include <regex>

namespace Zing { namespace Pepper { namespace StepDefinitions {

    class Step {

    public:

        Step(std::string const &expr,
             std::regex::flag_type flags = std::regex::ECMAScript);

        std::unique_ptr<Zing::App::Args> accepts(std::string const &string) const;

        virtual void operator()(Zing::App::Args &args) = 0;

        template <typename T>
        std::shared_ptr<T> world() const {
            return std::dynamic_pointer_cast<T>(_world);
        }

        void setWorld(std::shared_ptr<World> const &world);
        
    private:
        
        std::shared_ptr<World> _world;
        std::regex _expr;
        
    };

} } }
#endif /* defined(__DelegateTest__Step__) */
