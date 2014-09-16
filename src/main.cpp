#include <iostream>

#include <tfp.h>

// TODO: add comments

using namespace tfp;
using namespace tfp::number;
using namespace tfp::list;
using namespace tfp::string;
using namespace tfp::logic;
using namespace tfp::maybe;

struct maybe_lt_3
{
	using value = maybe_lt_3;

	template<typename N>
	struct bind
	{
		using value = apply<cond, apply<lt, N, num<3>>, apply<just, N>, nothing>;
	};
};

int main() {
	using inc = add::bind<num<1>>::value;
	std::cout << inc::bind<num<2>>::value::n << std::endl;
	std::cout << add::bind<num<1>>::value::bind<num<2>>::value::n << std::endl;
	std::cout << apply<add, num<1>, num<2>>::n << std::endl;
	using inc2 = apply<add, num<1>>;
	std::cout << inc2::bind<num<2>>::value::n << std::endl;
	using test_list = apply<cons, num<1>, apply<cons, num<2>, apply<cons, num<3>, nil::value>>>;
	std::cout << apply<length, test_list>::n << std::endl;
	std::cout << apply<head, test_list>::n << ' ' << apply<head, apply<map, inc, test_list>>::n << std::endl;
	std::cout << apply<to_str, str<'a', 'b', 'c'>>() << std::endl;
	std::cout << apply<to_str, num<-259>>() << std::endl;
	std::cout << apply<to_str, num<259>>() << std::endl;
	std::cout << apply<to_str, num<0>>() << std::endl;
	using complex_list = apply<cons, apply<cons, apply<just, num<-1>>, test_list>, apply<cons, str<'t', 'e', 's', 't', '\\', '\"'>,
		apply<cons, apply<ge, num<3>, num<3>>, apply<cons, nil::value, test_list>>>>;
	std::cout << apply<to_str, test_list>() << std::endl;
	std::cout << apply<to_str, complex_list>() << std::endl;
	std::cout << apply<to_str, apply<filter, is_list, complex_list>>() << std::endl;
	std::cout << apply<to_str, apply<foldl, add, num<0>, apply<filter, is_num, complex_list>>>() << std::endl;
	using fold_with_filter_and_map = apply<composition, apply<foldl, add, num<0>>, apply<composition, apply<map, inc>, apply<filter, is_num>>>;
	std::cout << apply<to_str, apply<fold_with_filter_and_map, complex_list>>() << std::endl;
	std::cout << apply<to_str, apply<map_maybe, maybe_lt_3, test_list>>() << std::endl;
	return 0;
}
