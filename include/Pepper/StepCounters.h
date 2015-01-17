//
//  StepCounters.h
//  Pepper
//
//  Created by Dave Meehan on 17/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_StepCounters_h
#define Pepper_StepCounters_h

namespace Pepper {

    class StepCounters {

    public:

        StepCounters()
        :
        _passed(0),
        _pending(0),
        _undefined(0),
        _skipped(0),
        _failures(0)
        {}

        size_t &passed() {
            return _passed;
        }

        size_t passed() const {
            return _passed;
        }

        size_t &pending() {
            return _pending;
        }

        size_t pending() const {
            return _pending;
        }

        size_t &undefined() {
            return _undefined;
        }

        size_t undefined() const {
            return _undefined;
        }

        size_t &skipped() {
            return _skipped;
        }

        size_t skipped() const {
            return _skipped;
        }

        size_t &failures() {
            return _failures;
        }

        size_t failures() const {
            return _failures;
        }

        size_t total() const {
            return _passed + _pending + _undefined + _skipped + _failures;
        }

    private:

        size_t                      _passed;
        size_t                      _pending;
        size_t                      _undefined;
        size_t                      _skipped;
        size_t                      _failures;
        
    };

}

#endif
