//
//  InvocationException.h
//  Pepper
//
//  Created by Dave Meehan on 16/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_InvocationException_h
#define Pepper_InvocationException_h

namespace Pepper {

    class InvocationException : public std::runtime_error {

    public:

        InvocationException(InvocationState const state,
                            std::string const &str)
        :
        _state(state),
        std::runtime_error(str)
        {}

        InvocationException(InvocationState const state,
                            char const *str)
        :
        _state(state),
        std::runtime_error(str)
        {}

    public:

        InvocationState     _state;
        
    };

}

#endif
