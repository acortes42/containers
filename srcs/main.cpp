/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 21:23:27 by adrian            #+#    #+#             */
/*   Updated: 2021/09/30 10:24:53 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/containers.hpp"

int main()
{
	ft::vector<int>	first(5, 50);
	ft::vector<int> second;
	ft::vector<int> empty;
	std::vector<int>real;
	int				*data;

	real.push_back(5);
	second.push_back(800);
	second.push_back(15);
	second.push_back(-900);
	first.push_back(10);
	second.resize(6, -50);
	std::cout << "aqui llega:  " << second.back() << std::endl;
	first.front() -= second.back();
	std::cout << "aqui llega: " << std::endl;
	second.at(1) -= second.front();
	second[4] = 0;
	data = second.data();
	data[3] = second[3] - 100;
	for(ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
	{ 
    	std::cout << *it << "\n";
	}
	std::cout << "este es size: " << second.size() << std::endl;
	std::cout << "este es capacity: " << second.capacity() << std::endl;
	std::cout << "este es el maz_size: " << second.max_size() << std::endl;
	std::cout << "este es el maz_size original: " << real.max_size() << std::endl;
	std::cout << "este es el empty cuando no esta vacio: " << first.empty() << std::endl;
	std::cout << "este es el empty cuando esta vacio: " << empty.empty() << std::endl;
	first.assign(3,-12);
	first.push_back(42);
	std::cout << "este es el valor final despues de un asign " << first[9] << std::endl;
	first.pop_back();
	std::cout << "este es el valor final despues de un asign " << first[8] << std::endl;
	try
	{
		std::cout << "este es el valor final despues de un asign " << first[9] << std::endl;
	}
	catch(...)
	{
		std::cerr << "--> Ninguno. Caiste en un error" << std::endl;
	}
	return (0);
}





/*
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}*/