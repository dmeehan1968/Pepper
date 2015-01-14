//
//  Feature.cpp
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#include "Feature.h"

namespace Pepper {

    void Feature::setWorld(std::shared_ptr<World> const &world) {
        _world = world;
    }

}