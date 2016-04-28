//============================================================================
// Name        : Arbori-AVL.cpp
// Author      : David Ivan
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

struct nod
{
	int info;
	int bal;
	nod *left, *right;
};

nod *r;

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

void echilibrare (nod *&p)
{
	if (p->bal == -2)
	{
		if (p->left->bal == 1)
			rotatie_stanga_dreapta(p);
		else rotatie_dreapta(p);
	}
	else
	{
		if (p->right->bal == -1)
			rotatie_dreapta_stanga(p);
		else
			rotatie_stanga(p);
	}
}

bool inserare (nod *&p, int val)
{
	if (p == NULL)
	{
		p = new nod; // de facut cu smart pointers
		p->info = val;
		p->bal = 0;
		p->left = NULL;
		p->right = NULL;
		return true;
	}

	if (p->info == val) return (false);

	if (p->info > val)
		if (inserare (p->left, val) == true)
			p->bal--;
		else return false;
	else
		if (inserare (p->right, val) == true)
			p->bal++;
		else return false;

	if ( p->bal == 0 || abs(p->bal) == 1)
		return true;
		else
		{
			echilibrare(p);
			return false;
		}
}
int main() {

	inserare (r, 5);
	inserare (r, 4);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
