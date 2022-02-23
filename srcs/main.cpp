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

	ft::vector<int>	second;
	ft::vector<int>	empty;
	
	ft::map<int, int>	map; 
	ft::map<int, int>	map2; 
	std::vector<int>	real;
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

	checker(etgrfawe.size() == etgrfawe2.size(), " vector constructor fill");
	checker(nhrbegfv.size() == nhrbegfv2.size(), " vector constructor range");
	checker(jytehrgfe.size() == jytehrgfe2.size(), " vector copy constructor");

	checker(second.max_size() == real.max_size(), " ft::vector::max_size() ==  std::vector::max_size() gives a failture");

	//first.push_back(10);
	
	second.resize(6, -50);
	real.resize(6, -50);
	
	checker(second.size() == real.size(), "Vector size() after resize");
	checker(*second.begin() == *real.begin(), "Vector begin() after resize");
	checker(*second.rbegin() == *real.rbegin(), "Vector rbegin() after resize");
	checker(*second.end() == *real.end(), "Vector end() after resize");
	std::cout << "rend -->" << *(second.rend() - 1) << " ----- " << *(real.rend() - 1) << std::endl;
	checker(*(second.rend() - 1) == *(real.rend() - 1), "Vector rend() after resize");

	// ft::vector<int>	first(second.begin() + 2, second.begin(), second.end());
/*
	ft::vector<int>::iterator it = second.begin();
	std::vector<int>::iterator real_it = real.begin();

	std::cout << "----  Check begin() and end()  ----- \n" << std::endl;
	while(it != second.end())
	{
		std::cout << ANSI_COLOR_CYAN<< *it << "  ==  " << *real_it << std::endl;
		it++;
		real_it++;
	}
*/
	checker(second.at(4) == real.at(4), "Vector at()");
	checker(second[2]  == real[2] , "vector []");

	// To check the copy constructor, just use empty 2 where empty it´s used

	empty = second;

	ft::vector<int> empty2(second);

	ft::vector<int>::iterator it_equal = empty.begin();
	ft::vector<int>::iterator second_it_equal = second.begin();

	std::cout << "----  Check begin() and end() after a equal----- \n" << std::endl;
	while(second_it_equal != second.end())
	{
		std::cout << ANSI_COLOR_CYAN<< *it_equal << "  ==  " << *second_it_equal << std::endl;
		it_equal++;
		second_it_equal++;
	}

	//insert: single element

	ft::vector<int>::iterator vect_it2;
	vect_it2 = second.begin() +2 ;
  	second.insert (vect_it2, 20);

	std::vector<int>::iterator vect_new_it2;
	vect_new_it2 = real.begin() + 2;
  	real.insert (vect_new_it2, 20);

	std::cout << *(second.begin() +2)  << " <-----> " <<   *(real.begin() + 2) <<std::endl;
	checker(*(second.begin() +2)  == *(real.begin() +2) , "Vector insert: single element");

	vect_it2 = second.begin();
	vect_new_it2 = real.begin();

	// insert: fill 

	second.insert (vect_it2, 4, -100);
	real.insert (vect_new_it2, 4, -100);

	std::cout << "First position : " << *(second.begin())  << " <-----> " <<   *(real.begin()) <<std::endl;
	std::cout << "First position + 2 : " << *(second.begin() +2)  << " <-----> " <<   *(real.begin() + 2) <<std::endl;
	checker(*(second.begin() +2)  == *(real.begin() +2) , "Vector insert: fill");

	//insert range

	vect_it2 = second.begin();
	vect_new_it2 = real.begin();

	second.insert (vect_it2, vect_it2, second.end());
	real.insert (vect_new_it2, vect_new_it2 , real.end());

	std::cout << "First position : " << *(second.begin())  << " <-----> " <<   *(real.begin()) <<std::endl;
	std::cout << "First position + 2 : " << *(second.begin() +2)  << " <-----> " <<   *(real.begin() + 2) <<std::endl;
	checker(*(second.begin())  == *(real.begin()) , "Vector insert: range");


	//front()

	checker(second.front()  == real.front() , "Vector front()");

	//back()

	std::cout << "Second back : " << second.back()  << " <-----> " <<   real.back() <<std::endl;
	checker(second.back()  == real.back() , "Vector back()	");

	//erase in range

	vect_it2 = second.begin();
	vect_new_it2 = real.begin();
	
	/*
		ft::vector<int>::iterator it = second.begin();
		std::vector<int>::iterator real_it = real.begin();

		std::cout << "----  Check begin() and end()  ----- \n" << std::endl;
		while(it != second.end())
		{
			std::cout << ANSI_COLOR_CYAN<< *it << "  ==  " << *real_it << std::endl;
			it++;
			real_it++;
		}
	*/

	second.erase (vect_it2, second.end());
	real.erase (vect_new_it2, real.end());

	
	ft::vector<int>::iterator it = second.begin();
	std::vector<int>::iterator real_it = real.begin();

	std::cout << "----  Check begin() and end()  ----- \n" << std::endl;
	while(it != second.end())
	{
		std::cout << ANSI_COLOR_CYAN<< *it << "  ==  " << *real_it << std::endl;
		it++;
		real_it++;
	}
	

	std::cout << "First position : " << *(second.begin())  << " <-----> " <<   *(real.begin()) <<std::endl;
	std::cout << "First position + 2 : " << *(second.begin() +2)  << " <-----> " <<   *(real.begin() + 2) <<std::endl;
	checker(*(second.begin())  == *(real.begin()) , "Vector after erase");

	//erase one item

	vect_it2 = second.begin();
	vect_new_it2 = real.begin();
	
	second.erase (vect_it2, second.end());
	real.erase (vect_new_it2, real.end());
	checker(*(second.begin())  == *(real.begin()) , "Vector after erase only one iterator");


	std::cout << "First position : " << *(second.begin())  << " <-----> " <<   *(real.begin()) <<std::endl;
	checker(*(second.begin())  == *(real.begin()) , "Vector after clear");
	
	second.resize(6, -50);
	real.resize(6, -50);

	second.push_back(-9);
	real.push_back(-9);
	second.pop_back();
	real.pop_back();
	std::cout << "Assign values : " << *(second.end() - 1)  << " <-----> " <<   *(real.end() - 1) <<std::endl;
	checker(*(second.end())  == *(real.end()) , "Vector pop_back");


	/**************************************************
	
						Stack
	
	**************************************************/


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



	/**************************************************
	
						Map
	
	**************************************************/
	

	std::cout << ANSI_COLOR_CYAN << "----  Start map  ----- \n" << ANSI_COLOR_RESET << std::endl;

	ft::map<int,int> mymap;
	std::map<int,int> mymap2;
	//mymap.find('c');
	
	mymap.insert(std::make_pair(982, 20));
	mymap2.insert(std::make_pair(982, 20));
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

	//checker(mymap.erase(6) == mymap2.erase(6), "Map: erase a value from key");
	//mymap.erase(6);
	//mymap2.erase(6);

	ft::map<int,int>::iterator new_it = mymap.find(5);
	std::map<int,int>::iterator new_it2 = mymap2.find(5);

	// std::cout << "results of find: "<< (*(new_it)).first << " ----- "<< (*(new_it2)).first <<std::endl;
	checker((*(new_it)).first == (*(new_it2)).first, "Comparing the return value of find(5)");

	 std::cout << "----------------------------------" << std::endl;

	mymap.insert(std::make_pair(43, 123));
	mymap2.insert(std::make_pair(43, 123));

	mymap.insert(std::make_pair(23, 1232));
	mymap2.insert(std::make_pair(23, 1232));

	mymap.insert(std::make_pair(4, 12));
	mymap2.insert(std::make_pair(100, 12));

	mymap.insert(std::make_pair(3, 12));
	mymap2.insert(std::make_pair(3, 12));

	mymap.insert(std::make_pair(2, 12));
	mymap2.insert(std::make_pair(2, 12));


	std::cout << "----------From rbegin to rend----------" << std::endl;

	for (std::map<int,int>::reverse_iterator mymap_it = mymap2.rbegin(); mymap_it != mymap2.rend(); ++mymap_it)
    	std::cout << ANSI_COLOR_GREEN << mymap_it->first << " => " << mymap_it->second << '\n';
	
	for (ft::map<int,int>::reverse_iterator mymap_it2 = mymap.rbegin(); mymap_it2 != mymap.rend(); ++mymap_it2)
    	std::cout << ANSI_COLOR_MAGENTA << mymap_it2->first << " => " << mymap_it2->second << '\n';

	std::cout << "----------From begin to end----------" << std::endl;


	for (std::map<int,int>::iterator mymap_it = mymap2.begin(); mymap_it != mymap2.end(); ++mymap_it)
    	std::cout << ANSI_COLOR_GREEN << mymap_it->first << " => " << mymap_it->second << '\n';

	for (ft::map<int,int>::iterator mymap_it2 = mymap.begin(); mymap_it2 != mymap.end(); ++mymap_it2)
    	std::cout << ANSI_COLOR_MAGENTA << mymap_it2->first << " => " << mymap_it2->second << '\n';


	std::cout << "----------End of main----------" << std::endl;
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