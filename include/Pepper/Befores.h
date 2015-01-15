//
//  Befores.h
//  Pepper
//
//  Created by Dave Meehan on 15/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_Befores_h
#define Pepper_Befores_h

#include "Before.h"

#include <list>

namespace Pepper {

    class Befores {

    public:

        void push_back(std::shared_ptr<Before> const &before) {
            _befores.push_back(before);
        }

        void accept(std::string const &name, Feature &feature) {

            for (auto &before : _befores) {

                auto args = before->accept(name);

                if (args) {

                    (*before)(feature, *args);

                }
            }
        }
        
    private:
        
        std::list<std::shared_ptr<Before>> _befores;
        
    };

}

#endif
