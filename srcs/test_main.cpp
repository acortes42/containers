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

	int *v_p;
	unsigned int i;
	  // allocate an array with space for 5 elements using vector's allocator:
	v_p = second.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i=0; i<5; i++) second.get_allocator().construct(&v_p[i],i);

	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << v_p[i];
	std::cout << '\n';

  	// destroy and deallocate:
	for (i=0; i<5; i++) second.get_allocator().destroy(&v_p[i]);
		second.get_allocator().deallocate(v_p,5);

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
	checker(*(second.rend() - 1) == *(real.rend() - 1), "Vector rend() after resize");

	checker(second.at(4) == real.at(4), "Vector at()");
	checker(second[2]  == real[2] , "vector []");

	// check the relational operators of a vector

	checker((second == second) == (real == real), " vector ==");
	checker((second != second) == (real != real), " vector !=");
	checker((second < second) == (real < real), " vector <");
	checker((second > second) == (real > real), " vector >");
	checker((second <= second) == (real <= real), " vector <=");
	checker((second >= second) == (real >= real), " vector >=");


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

	ft::map<int,int>::iterator new_it = mymap.find(5);
	std::map<int,int>::iterator new_it2 = mymap2.find(5);

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
	
	std::cout << "------------------------------------" << std::endl;

	checker(mymap.count(50) == mymap2.count(50), "Map count V1");
	checker(mymap.count(2) == mymap2.count(2), "Map count V2");

	mymap.value_comp();
	mymap2.value_comp();

	ft::map<int,int>::key_compare mycomp = mymap.key_comp();
	std::map<int,int>::key_compare mycomp2 = mymap2.key_comp();

	checker(mycomp(1,21) == mycomp2(1,21), "Map key_comp");

	ft::map<char,int>::iterator itlow,itup;

	std::cout << "Upper_bound of 9  in std  " << mymap2.upper_bound(9)->first  <<  std::endl;
	std::cout << "Upper_bound of 9  in ft  " << mymap.upper_bound(9)->first  << std::endl;

	checker(mymap.upper_bound(32)->first == mymap2.upper_bound(32)->first, "Map upper_bound");
	checker(mymap.lower_bound(32)->first == mymap2.lower_bound(32)->first, "Map lower_bound");

	std::pair<ft::map<int,int>::iterator,ft::map<int,int>::iterator> ret;
  	std::pair<std::map<int,int>::iterator,std::map<int,int>::iterator> ret2;

	ret = mymap.equal_range(32);
	ret2 = mymap2.equal_range(32);

	checker(ret.first->first == ret2.first->first, "Map equal_range first");
	checker(ret.second->first == ret2.second->first, "Map equal_range second");

	// (Exemple copied from cplusplus ) Allocate an array of 5 elements using mymap's allocator:

	std::pair<const int,int>* p;
	std::pair<const int,int>* p2;

	p= mymap.get_allocator().allocate(5);
	p2= mymap2.get_allocator().allocate(5);

	int psize = sizeof(ft::map<int,int>::value_type)*5;
	int psize2 = sizeof(std::map<int,int>::value_type)*5;

  	std::cout << "The allocated array has a size of " << psize << " bytes.\n";
	std::cout << "The allocated array has a size of " << psize2 << " bytes.\n";

	mymap.get_allocator().deallocate(p,5);
	mymap.get_allocator().deallocate(p2,5);
	checker(psize == psize2, "Map get_allocator");
	std::cout << "----------End of main----------" << std::endl;

	ft::map<int, int>	susy;
	std::map<int, int>	what;

	what.insert(std::make_pair(7.6f, 7));
	susy.insert(std::make_pair(7.6f, 7));
	susy.insert(std::make_pair(8, 9));
	susy.insert(std::make_pair(9, 7));
	susy.insert(std::make_pair(7, 3));

	std::cout << "WTF: " << (susy.find(10) == susy.end()) << std::endl;
	ft::map<int, int>::iterator susy_i = susy.begin();
	ft::map<int, int>::iterator	susy_last = susy.end();

	for ( ; susy_i != susy_last; ++susy_i)
	{
		std::cerr << "No me fío" << std::endl;
		susy.erase(susy_i);
	}
	
	return(0);
}