#pragma once

#include <tfp/base.h>
#include <tfp/string.h>

namespace tfp
{

	namespace bf
	{

		namespace helper
		{

			template <typename Operation>
			struct operation;

			template<int N>
			struct add
			{
				using value = add;
			};

			template<int N>
			struct move
			{
				using value = move;
			};

			struct read
			{
				using value = read;
			};

			struct write
			{
				using value = write;
			};

			template<typename... Operations>
			struct operation_list
			{
				using value = operation_list;
			};

			template<typename OpList>
			struct cycle
			{
				using value = OpList;
			};

			template<typename Str, typename... Output>
			struct parse;

			template<typename... Output>
			struct parse<string::str<>, Output...>
			{
				using value = operation_list<Output...>;
				using rest = string::str<>;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<'+', Str...>, Output...>
			{
				using value = typename parse<string::str<Str...>, Output..., add<1>>::value;
				using rest = typename parse<string::str<Str...>, Output..., add<1>>::rest;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<'-', Str...>, Output...>
			{
				using value = typename parse<string::str<Str...>, Output..., add<-1>>::value;
				using rest = typename parse<string::str<Str...>, Output..., add<-1>>::rest;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<'>', Str...>, Output...>
			{
				using value = typename parse<string::str<Str...>, Output..., move<1>>::value;
				using rest = typename parse<string::str<Str...>, Output..., move<1>>::rest;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<'<', Str...>, Output...>
			{
				using value = typename parse<string::str<Str...>, Output..., move<-1>>::value;
				using rest = typename parse<string::str<Str...>, Output..., move<-1>>::rest;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<'.', Str...>, Output...>
			{
				using value = typename parse<string::str<Str...>, Output..., write>::value;
				using rest = typename parse<string::str<Str...>, Output..., write>::rest;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<',', Str...>, Output...>
			{
				using value = typename parse<string::str<Str...>, Output..., read>::value;
				using rest = typename parse<string::str<Str...>, Output..., read>::rest;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<'[', Str...>, Output...>
			{
				using value = typename parse<typename parse<string::str<Str...>>::rest, Output..., cycle<typename parse<string::str<Str...>>::value>>::value;
				using rest = typename parse<typename parse<string::str<Str...>>::rest, Output..., cycle<typename parse<string::str<Str...>>::value>>::rest;
			};

			template<char... Str, typename... Output>
			struct parse<string::str<']', Str...>, Output...>
			{
				using value = operation_list<Output...>;
				using rest = string::str<Str...>;
			};

			template<int... Items>
			struct infinite_list
			{
				using value = infinite_list;
			};

			template<typename LeftPart, int Current, typename RightPart>
			struct tape;

			template<int Current, int... LeftPart, int... RightPart>
			struct tape<infinite_list<LeftPart...>, Current, infinite_list<RightPart...>>
			{
				using value = tape;
			};

			template<typename Tape, typename Operation>
			struct modify_tape;

			template<typename Tape>
			struct modify_tape<Tape, move<0>>
			{
				using value = Tape;
			};

			template<int Current, int... LeftPart, int RightItem, int... RightPart>
			struct modify_tape<tape<infinite_list<LeftPart...>, Current, infinite_list<RightItem, RightPart...>>, move<1>>
			{
				using value = tape<infinite_list<Current, LeftPart...>, RightItem, infinite_list<RightPart...>>;
			};

			template<int Current, int... LeftPart>
			struct modify_tape<tape<infinite_list<LeftPart...>, Current, infinite_list<>>, move<1>>
			{
				using value = tape<infinite_list<Current, LeftPart...>, 0, infinite_list<>>;
			};

			template<int Current, int LeftItem, int... LeftPart, int... RightPart>
			struct modify_tape<tape<infinite_list<LeftItem, LeftPart...>, Current, infinite_list<RightPart...>>, move<-1>>
			{
				using value = tape<infinite_list<LeftPart...>, LeftItem, infinite_list<Current, RightPart...>>;
			};

			template<int Current, int... RightPart>
			struct modify_tape<tape<infinite_list<>, Current, infinite_list<RightPart...>>, move<-1>>
			{
				using value = tape<infinite_list<>, 0, infinite_list<Current, RightPart...>>;
			};

			template<typename Tape>
			struct modify_tape<Tape, add<0>>
			{
				using value = Tape;
			};

			template<typename LeftPart, int Current, typename RightPart>
			struct modify_tape<tape<LeftPart, Current, RightPart>, add<1>>
			{
				using value = tape<LeftPart, (Current + 1 < 256 ? Current + 1 : 0), RightPart>;
			};

			template<typename LeftPart, int Current, typename RightPart>
			struct modify_tape<tape<LeftPart, Current, RightPart>, add<-1>>
			{
				using value = tape<LeftPart, (Current - 1 > -1 ? Current - 1 : 255), RightPart>;
			};

			template<typename Program, typename Tape, typename Input, typename Ouput>
			struct run;

			template<typename Tape, char... Input, char... Output>
			struct run<operation_list<>, Tape, string::str<Input...>, string::str<Output...>>
			{
				using value = string::str<Output...>;
				using tape = Tape;
				using input = string::str<Input...>;
				using output = string::str<Output...>;
			};

			template<template<int> class Operation, int N, typename... Operations, typename Tape, char... Input, char... Output>
			struct run<operation_list<Operation<N>, Operations...>, Tape, string::str<Input...>, string::str<Output...>>
			{
				using after_iteration = run<operation_list<Operations...>, typename modify_tape<Tape, Operation<N>>::value, string::str<Input...>, string::str<Output...>>;
				using value = typename after_iteration::value;
				using tape = typename after_iteration::tape;
				using input = typename after_iteration::input;
				using output = typename after_iteration::output;
			};

			template<typename... Operations, typename LeftPart, int Current, typename RightPart, char... Input, char... Output>
			struct run<operation_list<write, Operations...>, tape<LeftPart, Current, RightPart>, string::str<Input...>, string::str<Output...>>
			{
				using after_iteration = run<operation_list<Operations...>, tape<LeftPart, Current, RightPart>, string::str<Input...>, string::str<Output..., static_cast<char>(Current)>>;
				using value = typename after_iteration::value;
				using tape = typename after_iteration::tape;
				using input = typename after_iteration::input;
				using output = typename after_iteration::output;
			};

			template<typename... Operations, typename LeftPart, int Current, typename RightPart, char FirstChar, char... Input, char... Output>
			struct run<operation_list<read, Operations...>, tape<LeftPart, Current, RightPart>, string::str<FirstChar, Input...>, string::str<Output...>>
			{
				using after_iteration = run<operation_list<Operations...>, tape<LeftPart, static_cast<int>(FirstChar), RightPart>, string::str<Input...>, string::str<Output...>>;
				using value = typename after_iteration::value;
				using tape = typename after_iteration::tape;
				using input = typename after_iteration::input;
				using output = typename after_iteration::output;
			};

			template<typename Cycle, typename... Operations, typename LeftPart, typename RightPart, char... Input, char... Output>
			struct run<operation_list<cycle<Cycle>, Operations...>, tape<LeftPart, 0, RightPart>, string::str<Input...>, string::str<Output...>>
			{
				using after_iteration = run<operation_list<Operations...>, tape<LeftPart, 0, RightPart>, string::str<Input...>, string::str<Output...>>;
				using value = typename after_iteration::value;
				using tape = typename after_iteration::tape;
				using input = typename after_iteration::input;
				using output = typename after_iteration::output;
			};

			template<typename Cycle, typename... Operations, typename Tape, char... Input, char... Output>
			struct run<operation_list<cycle<Cycle>, Operations...>, Tape, string::str<Input...>, string::str<Output...>>
			{
				using after_iteration = run<Cycle, Tape, string::str<Input...>, string::str<Output...>>;
				using after_all_iterations = run<operation_list<cycle<Cycle>, Operations...>, typename after_iteration::tape, typename after_iteration::input, typename after_iteration::output>;

				using value = typename after_all_iterations::value;
				using tape = typename after_all_iterations::tape;
				using input = typename after_all_iterations::input;
				using output = typename after_all_iterations::output;
			};

		}

		// function that parses brainfuck program and returns tree of its operations
		struct parse
		{
			using value = parse;

			template<typename Str>
			struct bind
			{
				using value = typename helper::parse<Str>::value;
			};
		};

		// function that accepts brainfuck operation tree and executes it on given input string
		struct run
		{
			using value = run;

			template<typename Program>
			struct bind
			{
				struct value
				{
					template<typename Input>
					struct bind
					{
						using value = typename helper::run<Program, helper::tape<helper::infinite_list<>, 0, helper::infinite_list<>>, Input, string::str<>>::value;
					};
				};
			};
		};

		using parse_and_run = apply<composition, run, parse>;

	}

}
