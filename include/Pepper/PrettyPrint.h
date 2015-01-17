//
//  PrettyPrint.h
//  Pepper
//
//  Created by Dave Meehan on 15/01/2015.
//  Copyright (c) 2015 Replicated Solutions Limited. All rights reserved.
//

#ifndef Pepper_PrettyPrint_h
#define Pepper_PrettyPrint_h

#include "Formatter.h"
#include "FeatureInvocation.h"
#include "ScenarioInvocation.h"
#include "StepInvocation.h"

#include <ostream>
#include <chrono>
#include <math.h>

namespace Pepper {

    class PrettyPrint : public Formatter {

    public:

        enum class Colon {
            With,
            Without
        };

        PrettyPrint(std::shared_ptr<std::ostream> const &stream)
        :
        _stream(stream),
        _indent(0)
        {}

        void before(RootInvocation const &invocation) {

            _start = std::chrono::high_resolution_clock::now();

        }

        void after(RootInvocation const &invocation) {

            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _start);

            auto msecs = time.count();
            auto minutes = floor(msecs / 60000);
            msecs -= minutes * 60000;
            auto seconds = floor(msecs / 1000);
            msecs -= seconds * 1000;

            *_stream << minutes << "m" << seconds << "." << msecs << "s" << std::endl;

        }

        void before(FeatureInvocation const &invocation) override {

            *_stream << indent() << format(*invocation.node(), Colon::With) << std::endl;
            ++_indent;
            
        }

        void after(FeatureInvocation const &invocation) override {
            --_indent;

            *_stream << std::endl;
            
            *_stream << format("scenarios", invocation.scenarioCounters()) << std::endl;
            *_stream << format("steps", invocation.stepCounters()) << std::endl;

        }

        void before(ScenarioInvocation const &invocation) override {
            ++_indent;
        }

        void after(ScenarioInvocation const &invocation) override {

            --_indent;

            *_stream << std::endl << indent() << format(*invocation.node(), Colon::With) << std::endl;

            *_stream << _stepStream.str();

            _stepStream.str("");

        }

        void after(StepInvocation const &invocation) override {

            _stepStream << indent() << format(*invocation.node(), Colon::Without) << std::endl;

        }


    protected:

        std::string indent() const {

            return std::string(_indent * 2, ' ');

        }

        std::string format(Gherkin::Node const &node, Colon colon) const {

            auto keyword = node.keyword();
            if ( ! keyword.empty()) {
                keyword[0] = toupper(keyword[0]);
            }

            std::ostringstream os;
            os << keyword << (colon == Colon::With ? ": " : " ") << node.name();
            return os.str();
            
        }

        std::string format(std::string const &what, Counters const &counters) {

            std::ostringstream os;

            os  << indent()
                << counters.total() << " " << what;

            if (counters.total()) {
                os << " (";
            }

            bool comma = false;

            if (counters.failures()) {
                os << (comma ? ", " : "") << counters.failures() << " failed";
                comma = true;
            }

            if (counters.pending()) {
                os << (comma ? ", " : "") << counters.pending() << " pending";
                comma = true;
            }

            if (counters.undefined()) {
                os << (comma ? ", " : "") << counters.undefined() << " undefined";
                comma = true;
            }

            if (counters.skipped()) {
                os << (comma ? ", " : "") << counters.skipped() << " skipped";
                comma = true;
            }

            if (counters.passed()) {
                os << (comma ? ", " : "") << counters.passed() << " passed";
                comma = true;
            }

            if (counters.total()) {
                os << ")";
            }
            
            return os.str();

        }

    private:
        
        std::shared_ptr<std::ostream>   _stream;
        size_t                          _indent;
        std::ostringstream              _stepStream;

        std::chrono::high_resolution_clock::time_point  _start;

    };
    
}

#endif
