/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes	-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 21:23:27 by adrian            #+#    #+#             */
/*   Updated: 2022/02/01 13:46:56 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/containers.hpp"

void	checker(bool comparation, std::string str)
{
	std::cout << ANSI_COLOR_YELLOW<< "----------------------" << std::endl;
	std::cout << str << " : ";
	if (comparation)
		std::cout << ANSI_COLOR_GREEN << "OK" << std::endl;
	else
		std::cout << ANSI_COLOR_RED<< "FAILTURE!!!" << std::endl;
	std::cout << ANSI_COLOR_YELLOW<< "----------------------" << std::endl;
	std::cout << ANSI_COLOR_RESET << std::endl;
}

int main()
{

	ft::vector<int> second;
	ft::vector<int> empty;
	
	ft::map<int, int> map; 
	ft::map<int, int> map2; 
	std::vector<int>real;
	int x;
	//int				*data;

	checker(second.empty() == real.empty(), "Vector empty()");

	real.push_back(5);
	second.push_back(5);

	checker(second.size() == real.size(), "Vector size()");

	std::vector<int> werfda2;
	std::vector<int> etgrfawe2 (4,100);
	std::vector<int> nhrbegfv2 (etgrfawe2.begin(),etgrfawe2.end());
	std::vector<int> jytehrgfe2 (nhrbegfv2); 

	ft::vector<int> werfda;
	ft::vector<int> etgrfawe (4,100);
	ft::vector<int> nhrbegfv (etgrfawe.begin(),etgrfawe.end());
	ft::vector<int> jytehrgfe (nhrbegfv); 

	checker(second.max_size() == real.max_size(), " ft::vector::max_size() ==  std::vector::max_size() gives a failture");

	//first.push_back(10);
	
	second.resize(6, -50);
	real.resize(6, -50);
	
	checker(second.size() == real.size(), "Vector size() after resize");

	// ft::vector<int>	first(second.begin() + 2, second.begin(), second.end());

	ft::vector<int>::iterator it = second.begin();
	std::vector<int>::iterator real_it = real.begin();

	std::cout << "----  Check begin() and end()  ----- \n" << std::endl;
	while(it != second.end())
	{
		std::cout << ANSI_COLOR_CYAN<< *it << "  ==  " << *real_it << std::endl;
		it++;
		real_it++;
	}

	checker(second.at(4) == real.at(4), "Vector at()");

	ft::vector<int>::iterator vect_it2;
	vect_it2 = second.begin();
  	second.insert (vect_it2, 5, 300);

	std::vector<int>::iterator vect_new_it2;
	vect_new_it2 = real.begin();
  	real.insert (vect_new_it2, 5, 300);

	checker(*vect_new_it2 + 3 == *vect_it2 + 3, "Vector insert: fill");

	 x = 0;
	std::cout << ANSI_COLOR_CYAN << "----  Start stack  ----- \n" << ANSI_COLOR_RESET << std::endl;

	ft::stack<int> stak;
	std::stack<int> stak2;

	stak.push(12);
	stak.push(11);
	stak.push(10);

	stak2.push(12);
	stak2.push(11);
	stak2.push(10);

	//empty.assign(5, 100);
	//second.swap(empty);
	checker(stak.empty() == stak2.empty(), "Stack empty()");
	
	checker(stak.size() == stak2.size(), "Stack size()");

	checker(stak.top() == stak2.top(), "Stack top()");

	stak.pop();
	stak.pop();
	stak.pop();

	stak2.pop();
	stak2.pop();
	stak2.pop();

	checker(stak.size() == stak2.size(), "Stack size() after pop all values");

/*
	stak.pop();
	stak2.pop();
	checker(stak.size() == stak2.size(), "Stack size() after pop all values + 1 --> segfault forced");
*/

	std::cout << ANSI_COLOR_CYAN << "----  Start map  ----- \n" << ANSI_COLOR_RESET << std::endl;

	ft::map<int,int> mymap;
	std::map<int,int> mymap2;
	//mymap.find('c');
	
	mymap.insert(std::make_pair(5, 100));
	mymap2.insert(std::make_pair(5, 100));
	std::cout << "----------------------------------" << std::endl;

	mymap.insert(std::make_pair(6, 100));
	mymap2.insert(std::make_pair(6, 100));
	std::cout << "----------------------------------" << std::endl;
	
	mymap.insert(std::make_pair(4, 600));
	mymap2.insert(std::make_pair(4, 600));
		std::cout << "----------------------------------" << std::endl;
	
	mymap.insert(std::make_pair(100, 600));
	mymap2.insert(std::make_pair(100, 600));
		std::cout << "----------------------------------" << std::endl;

	mymap.insert(std::make_pair(100, 600));
	mymap2.insert(std::make_pair(100, 600));
		std::cout << "----------------------------------" << std::endl;
	

	checker(mymap[5] == mymap2[5], "Map[5]");
	checker(mymap[6] == mymap2[6], "Map[6]");
	checker(mymap[4] == mymap2[4], "Map[4]");
	checker(mymap[12] == mymap2[12], "Map[12]: without key 12");

	ft::map<int,int>::iterator new_it = mymap.find(5);
	std::map<int,int>::iterator new_it2 = mymap2.find(5);
	checker(new_it->first == new_it2->first, "Comparing the return value of find(5)");

	// std::cout << "----------------------------------" << std::endl;

	return(0);
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