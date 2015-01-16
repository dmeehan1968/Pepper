//
//  Status.h
//  Pepper
//
//  Created by Dave Meehan on 15/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_Status_h
#define Pepper_Status_h

#include <map>

namespace Pepper {

    enum class Status {
        Pending,
        Undefined,
        Skipped,
        Failed,
        Success
    };

    inline std::string to_string(Status const &status) {

        static auto map = std::map<Status, char const *>({

            { Status::Pending,      "Pending"       },
            { Status::Undefined,    "Undefined"     },
            { Status::Skipped,      "Skipped"       },
            { Status::Failed,       "Failed"        },
            { Status::Success,      "Success"       },

        });
        
        return map[status];
        
    }

}

#endif
