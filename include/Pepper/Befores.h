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

        template <class T, class... Args>
        void add(Args... args) {

            _befores.emplace_back(std::make_shared<T>(args...));

        }

        void accept(std::string const &name, Feature &feature) const {

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
