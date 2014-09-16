#pragma once

// Module with basic functions working with numbers

#include <tfp/types.h>
#include <tfp/string.h>

namespace tfp
{

	namespace number
	{

		// Numeric type
		// Numeric value can be accessed as template argument (compile-time)
		// or as static field n (both compile- and run-time)
		template<int N>
		struct num
		{
			using value = num;
			static constexpr const int n = N;
		};

		// Addition function
		struct add
		{
			using value = add;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = num<A::n + B::n>;
					};
				};
			};
		};

		// Subtraction function
		struct sub
		{
			using value = sub;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = num<A::n - B::n>;
					};
				};
			};
		};

		// Multiplication function
		struct mul
		{
			using value = mul;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = num<A::n * B::n>;
					};
				};
			};
		};

		// Division function
		struct div
		{
			using value = div;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = num<A::n / B::n>;
					};
				};
			};
		};

		// Mod function
		struct mod
		{
			using value = mod;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = num<A::n % B::n>;
					};
				};
			};
		};

		// Less than function
		struct lt
		{
			using value = lt;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = logic::logical_val<(A::n < B::n)>;
					};
				};
			};
		};

		// Less or equal function
		struct le
		{
			using value = le;

			template<typename A>
			struct bind
			{
				struct value
				{
					template<typename B>
					struct bind
					{
						using value = logic::logical_val<(A::n <= B::n)>;
					};
				};
			};
		};

		// Greater than function
		using gt = apply<flip, lt>;

		// Greater or equal function
		using ge = apply<flip, le>;

		namespace helper
		{

			template<typename E>
			struct is_num
			{
				using value = logic::logical_val<false>;
			};

			template<int N>
			struct is_num<num<N>>
			{
				using value = logic::logical_val<true>;
			};

			template<bool Lt0, bool ShowLeading0, int N>
			struct to_str;
			
			template<bool ShowLeading0, int N>
			struct to_str<true, ShowLeading0, N>
			{
				using value = apply<string::concat, string::str<'-'>, typename to_str<false, ShowLeading0, -N>::value>;
			};

			template<>
			struct to_str<false, true, 0>
			{
				using value = string::str<'0'>;
			};

			template<>
			struct to_str<false, false, 0>
			{
				using value = string::str<>;
			};

			template<bool ShowLeading0, int N>
			struct to_str<false, ShowLeading0, N>
			{
				using value = apply<string::concat, typename to_str<false, false, N / 10>::value, string::str<char('0' + (N % 10))>>;
			};

		}

		// Helper function that returns `logical_val<true>` if its argument is `num<N>`
		struct is_num
		{
			using value = is_num;

			template<typename E>
			struct bind
			{
				using value = typename helper::is_num<E>::value;
			};
		};

	}

	namespace string
	{

		namespace helper
		{

			// `to_str` specialization for `num` type
			template<int N>
			struct to_str<number::num<N>>
			{
				using value = typename number::helper::to_str<(N < 0), true, N>::value;
			};

		}

	}

}
