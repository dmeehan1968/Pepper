//
//  Statistic.h
//  Pepper
//
//  Created by Dave Meehan on 15/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_Statistic_h
#define Pepper_Statistic_h

namespace Pepper {

    class Statistic {

    public:

        Statistic() {

            clear();

        }

        void clear() {
            _total = _undefined = _skipped = _failed = 0;
        }

        void total(size_t const size) {
            _total = size;
        }

        void exception(std::shared_ptr<std::exception> const &e) {

            if (e) {
                _failed++;
            }

        }

        std::string str() const {

            std::ostringstream stream;
            stream << _total << " steps (";

            if (passed()) {
                stream << _total << " passed";

            } else {

                if (_failed) {
                    stream << _failed << " failed, " << (_total - (_skipped + _undefined + _failed)) << " passed";
                }

                if (_skipped) {
                    if (_failed) {
                        stream << ", ";
                    }
                    stream << _skipped << " skipped";
                }

                if (_undefined) {
                    if (_skipped || _failed) {
                        stream << ", ";
                    }
                    stream << _undefined << " undefined";
                }
            }

            stream << ")";

            return stream.str();
        }

        bool passed() const {
            return (_failed + _undefined + _skipped) == 0;
        }

        friend std::ostream & operator << (std::ostream &stream, Statistic const &stat) {

            stream << stat.str();
            return stream;

        }

    private:

        size_t  _total;
        size_t  _undefined;
        size_t  _skipped;
        size_t  _failed;
        
    };

}

#endif
