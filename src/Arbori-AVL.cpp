//============================================================================
// Name        : Arbori-AVL.cpp
// Author      : David Ivan
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <cstdlib>
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

nod* maxim (nod *r)
{
	if (!r)
	{
		cout<<"Arborele nu exista";
		exit(1);
	}

	while (r->right)
		r = r->right;
	return r;
}

nod* minim (nod *r)
{
	if (!r)
		{
			cout<<"Arborele nu exista";
			exit(1);
		}

	while (r->left)
		r = r->left;
	return r;
}

int cauta(nod *rad, int x)
{
    if (rad == NULL)
        return 0;

    if (rad->info == x)
        return 1;

    if (rad->info > x)
        return cauta(rad->left, x);

    return cauta(rad->right, x);

}

bool stergere (nod *&p, int val)
{
	if (p == NULL)
	{
		//std::cout<<"Arbore gol, nu se poate sterge";
		return false;
	}

	if (p->info > val)
	{
		if (stergere(p->left, val) == true)
			p->bal++;
		else return false;
	}
	else
		if (p->info < val)
		{
			if (stergere (p->right, val) == true)
				p->bal--;
			else return false;
		}
		else
		{
			if (p->left == NULL || p->right == NULL) // are cel mult un copil
			{
				if (p->left != NULL)
				{
					p->info = p->left->info;
					p->left = NULL;
					p->bal++;
					delete (p->left);
					return true;
					// poate delete(t->left) aici

				}
				else
					if (p->right != NULL)
					{
						p->info = p->right->info;
						p->right = NULL;
						p->bal--;
						delete (p->right);
						return true;
					}
			}
			else // are 2 copii
			{
				nod *t = minim(p->right);
				p->info = t->info;
				if (stergere (p->right, t->info) == true)
					p->bal--;
				else
					return false;
			}
		}

	if (p->bal != 0)
		echilibrare(p);

	if (p->bal == 0)
		return true;
	else
		return false;

}

void rsd (nod *rad)
{
    if (rad)
    {
        std::cout<<rad->info<<" ";
        rsd(rad->left);
        rsd(rad->right);
    }
}
int main() {

	inserare (r, 35);
	inserare (r, 37);
	inserare (r, 30);
	inserare (r, 50);
	inserare (r, 45);
	inserare (r, 40);
	inserare (r, 39);
	inserare (r, 42);
	inserare (r, 55);

	stergere(r, 45);
	stergere(r, 35);

	rsd (r);

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
