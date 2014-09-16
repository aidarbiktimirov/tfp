#pragma once

// Definition of basic types
// All of the values are typically templates
// that store actual values as template arguments

namespace tfp
{

	namespace number
	{

		template<int N>
		struct num;

	}

	namespace logic
	{

		template<bool B>
		struct logical_val;

	}

	namespace string
	{

		template<char... Str>
		struct str;

	}

}
