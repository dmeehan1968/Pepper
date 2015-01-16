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
#include "Statistic.h"
#include "Status.h"

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

        void before(Gherkin::Feature const &feature) override {

            *_stream << indent() << format(feature, Colon::With) << std::endl;
            ++_indent;

        }

        void after(Gherkin::Feature const &feature) override {

            --_indent;

        }

        void before(Gherkin::Scenario const &scenario) override {

            ++_indent;

        }

        void after(Gherkin::Scenario const &scenario) override {

            --_indent;

            *_stream << std::endl << indent() << format(scenario, Colon::With) << std::endl;

            *_stream << _stepStream.str();

            _stepStream.str("");

        }

        void after(Gherkin::Step const &step) override {

            _stepStream << indent() << format(step, Colon::Without) << std::endl;

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
