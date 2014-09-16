#pragma once

// Module with basic functions working with strings

#include <tfp/types.h>

namespace tfp
{

	namespace string
	{

		template<char... Str>
		struct str
		{
			using value = str;
		};

		namespace helper
		{

			template<typename Str1, typename Str2>
			struct concat;

			template<char... Str1, char... Str2>
			struct concat<str<Str1...>, str<Str2...>>
			{
				using value = str<Str1..., Str2...>;
			};

			template<typename Str>
			struct escape_str;

			template<char... Str>
			struct escape_str<str<'\"', Str...>>
			{
				using value = typename concat<str<'\\', '\"'>, typename escape_str<str<Str...>>::value>::value;
			};

			template<char... Str>
			struct escape_str<str<'\\', Str...>>
			{
				using value = typename concat<str<'\\', '\\'>, typename escape_str<str<Str...>>::value>::value;
			};

			template<char C, char... Str>
			struct escape_str<str<C, Str...>>
			{
				using value = typename concat<str<C>, typename escape_str<str<Str...>>::value>::value;
			};

			template<>
			struct escape_str<str<>>
			{
				using value = str<>;
			};

			template<typename Exp>
			struct to_str;

			template<char... Str>
			struct to_str<str<Str...>>
			{
				using value = typename concat<str<'\"'>, typename concat<typename escape_str<str<Str...>>::value, str<'\"'>>::value>::value;
			};

			template<typename E>
			struct is_str
			{
				using value = logic::logical_val<false>;
			};

			template<char... Str>
			struct is_str<str<Str...>>
			{
				using value = logic::logical_val<true>;
			};

		}

		// String concatenation function
		struct concat
		{
			using value = concat;

			template<typename Str1>
			struct bind
			{
				struct value
				{
					template<typename Str2>
					struct bind
					{
						using value = typename helper::concat<Str1, Str2>::value;
					};
				};
			};
		};

		// `to_str` function that returns string representation of its argument
		// If you want to make that function work with new types you should
		// create `string::helper::to_str` specialization for that type
		struct to_str
		{
			using value = to_str;

			template<typename Exp>
			struct bind
			{
				using value = typename helper::to_str<Exp>::value;
			};
		};

		// `is_str` helper that returns `logical_val<true>` if its argument is `str`
		struct is_str
		{
			using value = is_str;

			template<typename E>
			struct bind
			{
				using value = typename helper::is_str<E>::value;
			};
		};

	}

}
