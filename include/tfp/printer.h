#pragma once

// Helpers used to print tfp values to `std::ostream`s

#include <string>
#include <iostream>

#include <tfp/string.h>

namespace tfp
{

	namespace string
	{

		template<char... Str>
		std::ostream &operator<<(std::ostream &s, const str<Str...> &)
		{
			return s << std::string{ Str... };
		}

	}

}
