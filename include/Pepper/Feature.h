//
//  Feature.h
//  DelegateTest
//
//  Created by Dave Meehan on 09/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef __DelegateTest__Feature__
#define __DelegateTest__Feature__

#include <memory>

namespace Pepper {

    class World;

    class Feature {

    public:

        void setWorld(std::shared_ptr<World> const &world);

        template <typename T>
        std::shared_ptr<T> world() {

            return std::dynamic_pointer_cast<T>(_world);

        }

    private:

        std::shared_ptr<World>      _world;
        
    };

}

#endif /* defined(__DelegateTest__Feature__) */
