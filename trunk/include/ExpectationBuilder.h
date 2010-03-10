#pragma once
#ifndef INCLUDED_CALLMATCHER_H
#define INCLUDED_CALLMATCHER_H

#include "NullType.h"
#include "Matcher.h"
#include <boost/shared_ptr.hpp>
#include "IRegistry.h"

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <hamcrest/core/hc_matcher.h>

#include "Any.h"

namespace carnamock {

	template <class RegistryType>
	class ExpectationBuilder 
	{
		RegistryType &registry;

	public:
		typedef boost::shared_ptr<ExpectationBuilder<RegistryType> > Ptr;

		~ExpectationBuilder() {}

		ExpectationBuilder(RegistryType &_registry) : registry(_registry), paramWasSetted(false) {}

		template <class Param1>
		ExpectationBuilder &WithParams(const hamcrest::matcher<Param1> &p1)
		{
			//if this fail to compile is because the type of your matcher is not the same from the function mocked
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 1);
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(p1.copy()));
			paramWasSetted= true;
			return *this;
		}

		template <class Param1, class Param2>
		ExpectationBuilder &WithParams(const hamcrest::matcher<Param1> &p1, const hamcrest::matcher<Param2> &p2)
		{
			//if this fail to compile is because the type of your matcher is not the same from the function mocked
			BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 2);
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(p1.copy()));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(p2.copy()));
			paramWasSetted= true;
			return *this;
		}

		template <class Param1, class Param2, class Param3>
		ExpectationBuilder &WithParams(const hamcrest::matcher<Param1> &p1
			, const hamcrest::matcher<Param2> &p2, const hamcrest::matcher<Param3> &p3)
		{
			//if this fail to compile is because the type of your matcher is not the same from the function mocked
			BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 3);
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param3, Param3>::value));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(p1.copy()));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(p2.copy()));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param3>, Param3>(p3.copy()));
			paramWasSetted= true;
			return *this;
		}

		template <class Param1, class Param2, class Param3, class Param4>
		ExpectationBuilder &WithParams(const hamcrest::matcher<Param1> &p1
			, const hamcrest::matcher<Param2> &p2, const hamcrest::matcher<Param3> &p3, const hamcrest::matcher<Param4> &p4)
		{
			//if this fail to compile is because the type of your matcher is not the same from the function mocked
			BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 4);
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param3, Param3>::value));
			BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param4, Param4>::value));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(p1.copy()));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(p2.copy()));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param3>, Param3>(p3.copy()));
			matchers.push_back(new IMatcherWrapper<hamcrest::matcher<Param4>, Param4>(p4.copy()));
			paramWasSetted= true;
			return *this;
		}

		void Times(size_t times)
		{
         for (unsigned j= 0; j < times; j++) {
         	Expectation *expectation= new Expectation();
            for (unsigned i= 0; i < RegistryType::RegistryTraits::NrParams; i++)
				   expectation->AddParamMatcher(paramWasSetted ? matchers[i] : new Any());
   			registry.AddExpectation(expectation);
         }
		}

		bool paramWasSetted;
		std::vector<IMatcher*> matchers;
	};

} //namespace carnamock

#endif 