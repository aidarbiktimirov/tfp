#include <iostream>

#include <tfp.h>

using namespace tfp;
using namespace tfp::string;
using namespace tfp::bf;

int main() {
	// Hello, world
	using program1 = str<'+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '[', '>', '+', '+', '+', '+', '+', '+', '+', '>',
		'+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '>', '+', '+', '+', '<', '<', '<', '-', ']', '>', '+', '+', '.', '>', '+',
		'.', '+', '+', '+', '+', '+', '+', '+', '.', '.', '+', '+', '+', '.', '>', '+', '+', '.', '<', '<', '+', '+', '+', '+', '+',
		'+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '.', '>', '.', '+', '+', '+', '.', '-', '-', '-', '-', '-', '-', '.', '-',
		'-', '-', '-', '-', '-', '-', '-', '.', '>', '+', '.'>;
	using parsed_program1 = apply<parse, program1>;
	using program_output1 = apply<run, parsed_program1, string::str<>>;
	std::cout << apply<to_str, program_output1>() << std::endl;

	// Example with reading
	using program2 = str<',', '[', '.', ',', ']'>;
	std::cout << apply<to_str, apply<parse_and_run, program2, str<'T', 'e', 's', 't', '\0'>>>() << std::endl;
}
