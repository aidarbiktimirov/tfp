#pragma once

// Definition of `apply` helper that allows to call functions easier

namespace tfp
{

	// Implementation of helpers are typically defined inside `helper` namespace
	namespace helper
	{

		template<typename F, typename... Args>
		struct apply;

		template<typename F>
		struct apply<F>
		{
			using value = F;
		};

		template<typename F, typename Arg, typename... Args>
		struct apply<F, Arg, Args...>
		{
			using value = typename apply<typename F::template bind<Arg>::value, Args...>::value;
		};

	}

	// `apply` helper that allows to call functions like that:
	//     apply<f, arg0, arg1, ...>
	// instead of:
	//     f::bind<arg0>::value::bind<arg1>::value::...
	// It's possible to write `apply<f>` without arguments: the result will be `f` itself
	template<typename F, typename... Args>
	using apply = typename helper::apply<F, Args...>::value;

}
