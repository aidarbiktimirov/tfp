#pragma once

// Module with basic functions working with boolean values

#include <tfp/base.h>
#include <tfp/types.h>
#include <tfp/string.h>

namespace tfp
{

	namespace logic
	{

		template<bool B>
		struct logical_val
		{
			using value = logical_val;
			static constexpr const bool b = B;
		};

		namespace helper
		{

			template<typename A, typename B>
			struct eq
			{
				using value = logical_val<false>;
			};

			template<typename A>
			struct eq<A, A>
			{
				using value = logical_val<true>;
			};

			template<typename P, typename T, typename F>
			struct cond;

			template<typename T, typename F>
			struct cond<logical_val<true>, T, F>
			{
				using value = T;
			};

			template<typename T, typename F>
			struct cond<logical_val<false>, T, F>
			{
				using value = F;
			};

			template<typename E>
			struct is_logical_val
			{
				using value = logical_val<false>;
			};

			template<bool B>
			struct is_logical_val<logical_val<B>>
			{
				using value = logical_val<true>;
			};

		}

		// Logical and operation
		struct logical_and
		{
			using value = logical_and;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = logical_val<A::b && B::b>;
					};
				};
			};
		};

		// Logical or operation
		struct logical_or
		{
			using value = logical_and;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = logical_val<A::b || B::b>;
					};
				};
			};
		};

		// Logical not operation
		struct logical_not
		{
			using value = logical_and;

			template<typename A>
			struct bind
			{
				using value = logical_val<!A::b>;
			};
		};

		// Equality operator that returns `logical_val<true>` if both of its arguments are the same
		struct eq
		{
			using value = eq;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = typename helper::eq<A, B>::value;
					};
				};
			};
		};

		struct ne
		{
			using value = ne;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = apply<logical_not, typename helper::eq<A, B>::value>;
					};
				};
			};
		};

		// Ternary operator that returns `T` if `P` is `logical_value<true>` and `F` otherwise
		struct cond
		{
			using value = cond;

			template<typename P>
			struct bind
			{
				struct value
				{
					template<typename T>
					struct bind
					{
						struct value
						{
							template<typename F>
							struct bind
							{
								using value = typename helper::cond<P, T, F>::value;
							};
						};
					};
				};
			};
		};

		// `is_logical_val` helper that returns `logical_val<true>` if its argument is `logical_val`
		struct is_logical_val
		{
			using value = is_logical_val;

			template<typename E>
			struct bind
			{
				using value = typename helper::is_logical_val<E>::value;
			};
		};

	}

	namespace string
	{

		namespace helper
		{

			// `to_str` specialization for `logical_val` type
			template<>
			struct to_str<logic::logical_val<true>>
			{
				using value = str<'T', 'r', 'u', 'e'>;
			};

			template<>
			struct to_str<logic::logical_val<false>>
			{
				using value = str<'F', 'a', 'l', 's', 'e'>;
			};

		}

	}

}
