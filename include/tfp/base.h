#pragma once

// Module with basic functions
// All the functions are structures that have next things:
// 1. `value` alias (required) that refers to structure itself
// 2. `bind` template (optional) with exactly one template argument,
//     its structure must subject to the same rules (but instead of
//     having `value` as alias it may be nested structure)

#include <tfp/apply.h>

namespace tfp
{

	// Composition of two functions
	// Haskell's analogue of dot operator:
	//     (.) f g x = f $ g x
	// composition(f, g, x) = f(g(x))
	struct composition
	{
		using value = composition;

		template<typename F>
		struct bind
		{
			struct value
			{
				template<typename G>
				struct bind
				{
					struct value
					{
						template<typename X>
						struct bind
						{
							using value = apply<F, apply<G, X>>;
						};
					};
				};
			};
		};
	};

	// Argument flip function
	// Haskell's analogue of `flip` function:
	//     flip f x y = f y x
	// flip(f, x, y) = f(y, x)
	struct flip
	{
		using value = flip;

		template<typename F>
		struct bind
		{
			struct value
			{
				template<typename X>
				struct bind
				{
					struct value
					{
						template<typename Y>
						struct bind
						{
							using value = apply<F, Y, X>;
						};
					};
				};
			};
		};
	};

	// Identity function
	// Haskell's analogue of `id` function:
	//     id x = x
	// id(x) = x
	struct id
	{
		using value = id;

		template<typename Exp>
		struct bind
		{
			using value = Exp;
		};
	};

}
