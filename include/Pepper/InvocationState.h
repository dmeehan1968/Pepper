//
//  InvocationState.h
//  Pepper
//
//  Created by Dave Meehan on 16/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_InvocationState_h
#define Pepper_InvocationState_h

namespace Pepper {

    enum class InvocationState {
        Pending,
        Undefined,
        Skipped,
        Failed,
        Passed
    };

    char const *to_string(InvocationState const &state) {

        switch (state) {
            case InvocationState::Pending:
                return "Pending";

            case InvocationState::Undefined:
                return "Undefined";

            case InvocationState::Skipped:
                return "Skipped";

            case InvocationState::Failed:
                return "Failed";

            case InvocationState::Passed:
                return "Passed";

        }
        
        throw std::runtime_error("Unknown InvocationState");
        
    }

}

#endif
