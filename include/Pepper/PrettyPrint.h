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


        void before(FeatureInvocation const &invocation) override {

            *_stream << indent() << format(*invocation.node(), Colon::With) << std::endl;
            ++_indent;
            
        }

        void after(FeatureInvocation const &invocation) override {
            --_indent;

            *_stream    << indent() << std::endl
                        << invocation.total() << " steps";

            if (invocation.total()) {
                *_stream << " (";
            }

            bool comma = false;

            if (invocation.failures()) {
                *_stream << (comma ? ", " : "") << invocation.failures() << " failed";
                comma = true;
            }

            if (invocation.pending()) {
                *_stream << (comma ? ", " : "") << invocation.pending() << " pending";
                comma = true;
            }

            if (invocation.undefined()) {
                *_stream << (comma ? ", " : "") << invocation.undefined() << " undefined";
                comma = true;
            }

            if (invocation.skipped()) {
                *_stream << (comma ? ", " : "") << invocation.skipped() << " skipped";
                comma = true;
            }

            if (invocation.passed()) {
                *_stream << (comma ? ", " : "") << invocation.passed() << " passed";
                comma = true;
            }

            if (invocation.total()) {
                *_stream << ")";
            }

            *_stream << std::endl;

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

    private:
        
        std::shared_ptr<std::ostream>   _stream;
        size_t                          _indent;
        std::ostringstream              _stepStream;

    };
    
}

#endif
