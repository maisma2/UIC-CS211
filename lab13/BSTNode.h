/* Name: Abeer Ismail
* Header for BSTNode.cpp
*/
// BSTNode.h

#ifndef BSTNODE_H

	#define BSTNODE_H

	#include <cstdlib>
	#include <iostream>
	
	using namespace std;
	
	class BSTNode {
		
		private:
			int data, count;
			BSTNode * left, * right;
			
		public:
			BSTNode( int d );
			~BSTNode( );
			void add( int d );
			void print( );			
	};
	
#endif
