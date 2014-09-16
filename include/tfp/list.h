#pragma once

// Module with list type and functions working with lists

#include <tfp/string.h>
#include <tfp/logic.h>

namespace tfp
{

	namespace list
	{

		template<typename List>
		struct list;

		namespace helper
		{

			struct nil
			{
				using value = nil;
			};

			template<typename Head, typename Tail>
			struct cons;

			template<typename Head>
			struct cons<Head, list<nil>>
			{
				using value = cons;
			};

			template<typename Head, typename TailHead, typename TailTail>
			struct cons<Head, list<cons<TailHead, TailTail>>>
			{
				using value = cons;
			};

			template<typename List>
			struct head;

			template<typename Head, typename Tail>
			struct head<list<cons<Head, Tail>>>
			{
				using value = Head;
			};

			template<typename List>
			struct tail;

			template<typename Head, typename Tail>
			struct tail<list<cons<Head, Tail>>>
			{
				using value = Tail;
			};

			template<typename List>
			struct length;

			template<>
			struct length<list<nil>>
			{
				using value = number::num<0>;
			};

			template<typename Head, typename Tail>
			struct length<list<cons<Head, Tail>>>
			{
				using value = apply<number::add, number::num<1>, typename length<Tail>::value>;
			};

			template<typename F, typename List>
			struct map;

			template<typename F>
			struct map<F, list<nil>>
			{
				using value = list<nil>;
			};

			template<typename F, typename Head, typename Tail>
			struct map<F, list<cons<Head, Tail>>>
			{
				using value = list<cons<typename F::template bind<Head>::value, typename map<F, Tail>::value>>;
			};

			template<typename Pred, typename List>
			struct filter;

			template<typename Pred>
			struct filter<Pred, list<nil>>
			{
				using value = list<nil>;
			};

			template<typename Pred, typename Head, typename Tail>
			struct filter<Pred, list<cons<Head, Tail>>>
			{
				using filteredTail = typename filter<Pred, Tail>::value;
				using value = apply<logic::cond, apply<Pred, Head>, list<cons<Head, filteredTail>>, filteredTail>;
			};

			template<typename F, typename Initial, typename List>
			struct foldl;

			template<typename F, typename Initial>
			struct foldl<F, Initial, list<nil>>
			{
				using value = Initial;
			};
			
			template<typename F, typename Initial, typename Head, typename Tail>
			struct foldl<F, Initial, list<cons<Head, Tail>>>
			{
				using value = typename foldl<F, apply<F, Initial, Head>, Tail>::value;
			};

			template<typename List>
			struct to_str;

			template<>
			struct to_str<list<nil>>
			{
				using value = string::str<'[', ']'>;
			};

			template<typename Head>
			struct to_str<list<cons<Head, list<nil>>>>
			{
				using value = apply<string::to_str, Head>;
			};

			template<typename Head, typename Tail>
			struct to_str<list<cons<Head, Tail>>>
			{
				using value = apply<string::concat, apply<string::to_str, Head>, apply<string::concat, string::str<',', ' '>, typename to_str<Tail>::value>>;
			};

			template<typename E>
			struct is_list
			{
				using value = logic::logical_val<false>;
			};

			template<typename E>
			struct is_list<list<E>>
			{
				using value = logic::logical_val<true>;
			};

		}

		// Empty list
		template<>
		struct list<helper::nil>
		{
			using value = list;
		};

		// Non-empty list
		template<typename Head, typename Tail>
		struct list<helper::cons<Head, list<Tail>>>
		{
			using value = list;
		};

		// Empty list ctor
		struct nil
		{
			using value = list<helper::nil>;
		};

		// Non-empty list ctor
		// Accepts two arguments: head and tail of list
		struct cons
		{
			using value = cons;

			template<typename Head>
			struct bind
			{
				struct value
				{
					template<typename Tail>
					struct bind
					{
						using value = list<typename helper::cons<Head, Tail>::value>;
					};
				};
			};
		};

		// Head extraction function
		struct head
		{
			using value = head;

			template<typename List>
			struct bind
			{
				using value = typename helper::head<List>::value;
			};
		};

		// Tail extraction function
		struct tail
		{
			using value = tail;

			template<typename List>
			struct bind
			{
				using value = typename helper::tail<List>::value;
			};
		};

		// List length function
		struct length
		{
			using value = length;

			template<typename List>
			struct bind
			{
				using value = typename helper::length<List>::value;
			};
		};

		// Function that applies function `F` to every element of `List`
		// Haskell's analogue of `map` function
		struct map
		{
			using value = map;

			template<typename F>
			struct bind
			{
				struct value
				{
					template<typename List>
					struct bind
					{
						using value = typename helper::map<F, List>::value;
					};
				};
			};
		};

		// Function that removes elements of list for which `Pred` returns `logical_val<false>`
		// Haskell's analogue of `filter` function
		struct filter
		{
			using value = filter;

			template<typename Pred>
			struct bind
			{
				struct value
				{
					template<typename List>
					struct bind
					{
						using value = typename helper::filter<Pred, List>::value;
					};
				};
			};
		};

		// Left fold
		// Haskell's analogue of `foldl` function
		struct foldl
		{
			using value = foldl;

			template<typename F>
			struct bind
			{
				struct value
				{
					template<typename Initial>
					struct bind
					{
						struct value
						{
							template<typename List>
							struct bind
							{
								using value = typename helper::foldl<F, Initial, List>::value;
							};
						};
					};
				};
			};
		};

		// `is_list` helper function that returns `logical_val<true>` if its argument is `list`
		struct is_list
		{
			using value = is_list;

			template<typename E>
			struct bind
			{
				using value = typename helper::is_list<E>::value;
			};
		};

	}

	namespace string
	{

		namespace helper
		{

			// `to_str` specialization for `list` type
			template<>
			struct to_str<list::list<list::helper::nil>>
			{
				using value = typename list::helper::to_str<list::list<list::helper::nil>>::value;
			};

			template<typename Head, typename Tail>
			struct to_str<list::list<list::helper::cons<Head, Tail>>>
			{
				using value = apply<string::concat, str<'['>, apply<string::concat,
					typename list::helper::to_str<apply<list::cons, Head, Tail>>::value, str<']'>>>;
			};

		}

	}

}
