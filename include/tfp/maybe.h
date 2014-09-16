#pragma once

// Module with `maybe` type
// Analogue of Haskell's type `Maybe`

#include <tfp/string.h>
#include <tfp/list.h>

namespace tfp
{

	namespace maybe
	{

		template<typename E>
		struct maybe;

		namespace helper
		{

			struct nothing
			{
				using value = nothing;
			};

			template<typename E>
			struct just
			{
				using value = just;
			};

			template<typename E>
			struct to_str;

			template<>
			struct to_str<nothing>
			{
				using value = string::str<'N', 'o', 't', 'h', 'i', 'n', 'g'>;
			};

			template<typename E>
			struct to_str<just<E>>
			{
				using value = apply<string::concat, string::str<'J', 'u', 's', 't', ' ', '('>,
					apply<string::concat, apply<string::to_str, E>, string::str<')'>>>;
			};

			template<typename E>
			struct is_maybe
			{
				using value = logic::logical_val<false>;
			};

			template<typename E>
			struct is_maybe<maybe<E>>
			{
				using value = logic::logical_val<true>;
			};

			template<typename E>
			struct is_nothing
			{
				using value = logic::logical_val<false>;
			};

			template<>
			struct is_nothing<maybe<nothing>>
			{
				using value = logic::logical_val<true>;
			};

			template<typename E>
			struct is_just
			{
				using value = logic::logical_val<false>;
			};

			template<typename E>
			struct is_just<maybe<just<E>>>
			{
				using value = logic::logical_val<true>;
			};

			template<typename E>
			struct from_just;

			template<typename E>
			struct from_just<maybe<just<E>>>
			{
				using value = E;
			};

		}

		// Maybe without value
		template<>
		struct maybe<helper::nothing>
		{
			using value = maybe;
		};

		// Maybe with value `E`
		template<typename E>
		struct maybe<helper::just<E>>
		{
			using value = maybe;
		};

		// `nothing` ctor
		struct nothing
		{
			using value = maybe<typename helper::nothing>;
		};

		// `just` ctor
		struct just
		{
			using value = just;

			template<typename E>
			struct bind
			{
				using value = maybe<typename helper::just<E>::value>;
			};
		};

		// `is_maybe` helper function that returns `logical_val<true>` if its argument is `maybe`
		struct is_maybe
		{
			using value = is_maybe;

			template<typename E>
			struct bind
			{
				using value = typename helper::is_maybe<E>::value;
			};
		};

		// `is_nothing` helper function that returns `logical_val<true>` if its argument is `nothing`
		struct is_nothing
		{
			using value = is_nothing;

			template<typename E>
			struct bind
			{
				using value = typename helper::is_nothing<E>::value;
			};
		};

		// `is_just` helper function that returns `logical_val<true>` if its argument is `just`
		struct is_just
		{
			using value = is_just;

			template<typename E>
			struct bind
			{
				using value = typename helper::is_just<E>::value;
			};
		};

		// `from_just` helper function that returns `E` if its argument is `just<E>`
		struct from_just
		{
			using value = from_just;

			template<typename E>
			struct bind
			{
				using value = typename helper::from_just<E>::value;
			};
		};

		// Function that removes `nothing`s from list and extracts values from `just`s
		// Haskell's analogue of `catMaybes` function:
		//     catMaybes = (map fromJust) . (filter isJust)
		using cat_maybes = apply<composition, apply<list::map, from_just>, apply<list::filter, is_just>>;

		// Function that applies function `F` to each element of list and then applies `cat_maybes` to result
		// Haskell's analogue of `mapMaybe` function:
		//     mapMaybe = catMaybes . (map f)
		struct map_maybe
		{
			using value = map_maybe;

			template<typename F>
			struct bind
			{
				using value = apply<composition, cat_maybes, apply<list::map, F>>;
			};
		};

	}

	namespace string
	{

		namespace helper
		{

			template<typename E>
			struct to_str<maybe::maybe<E>>
			{
				using value = typename maybe::helper::to_str<E>::value;
			};

		}

	}

}
