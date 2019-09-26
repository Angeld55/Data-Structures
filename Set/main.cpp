#include "Set.hpp"
#include <iostream>


int main()
{
	Set<int> s;

	s.Add(3);
	s.Add(12);
	s.Add(15);
	s.Add(17);

	Set<int> s2;
	s2.Add(15);
	s2.Add(17);
	s2.Add(19);

	Set<int> s3 = Intersection(s, s2);  //s3 is [15, 17]


}
