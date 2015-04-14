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
	using parsed_program1 = parse<program1>;
	using program_output1 = run<parsed_program1>;
	std::cout << apply<to_str, program_output1>() << std::endl;

	// Example with reading
	using program2 = str<',', '[', '.', ',', ']'>;
	using parsed_program2 = parse<program2>;
	using program_output2 = run<parsed_program2, str<'T', 'e', 's', 't', '\0'>>;
	std::cout << apply<to_str, program_output2>() << std::endl;
}
