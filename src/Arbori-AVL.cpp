//============================================================================
// Name        : Arbori-AVL.cpp
// Author      : David Ivan
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

struct nod
{
	int info;
	int bal;
	nod *left, *right;
};

void rotatie_dreapta(nod *&p)
{
	nod *t = p->left;
	p->left = t->right;
	t->right = p;
	p->bal = p->bal + (1 - min(t->bal, 0));
	t->bal = t->bal + (1 + max(p->bal, 0));
	p = t;
}

void rotatie_stanga(nod *&p)
{
	nod *t = p->right;
	p->right = t->left;
	t->left = p;
	p->bal = p->bal - (1+ max(t->bal, 0));
	t->bal = t->bal - (1-min(p->bal, 0));
	p = t;
}

void rotatie_dreapta_stanga (nod *&p)
{
	rotatie_dreapta(p->right);
	rotatie_stanga(p);
}

void rotatie_stanga_dreapta (nod *&p)
{
	rotatie_stanga(p->left);
	rotatie_dreapta(p);
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
