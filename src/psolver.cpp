#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include <algorithm>

// Définitions des contraintes, d'autres contraintes peuvent être ajoutée en respectant cette signature
typedef bool (*CONTRAINTE) (const std::vector<bool>& mat, int n, int q);

// Puissance avec unsigned long long int
unsigned long long int ipow(unsigned long long int base, int exp ) {
    unsigned long long int result = 1ULL;
    while( exp ) {
        if ( exp & 1 ) {
            result *= (unsigned long long int)base;
        }
        exp >>= 1;
        base *= base;
    }
    return result;
}

// Contrainte 1 pigeon est affecté à 1 et 1 seul pigeonnier
bool contrainte1(const std::vector<bool>& mat, int n, int q) {
	unsigned int tmp;
	for(int i=0; i < n; ++i) {
		tmp = 0;
		for(int j=0; j < q; ++j) {
			tmp += mat[i*q+j];
		}

		if(tmp != 1)
			return false;
	}

	return true;
}

// Contrainte 1 pigeonnier ne doit pas contenir + de 1 pigeon
bool contrainte2(const std::vector<bool>& mat, int n, int q) {
	unsigned int tmp;
	for(int i=0; i < q; ++i) {
		tmp = 0;
		for(int j=0; j < n; ++j) {
			tmp += mat[j*q+i];
		}

		if(tmp > 1)
			return false;
	}

	return true;
}

// Convertis un unsigned long long int en représentation binaire dans la matrice
void conv(std::vector<bool>& mat, unsigned long long int init) {
	for(int i=mat.size()-1; i >= 0; --i) {
		mat[i] = init%2;
		init = init >> 1;
	}
}

bool solve(int n, int q, std::vector<CONTRAINTE> contraintes) {
	unsigned int satisfiable = 0;
	unsigned long long int nbSol = ipow(2,(n*q)); // Nombre de matrices possible
	unsigned long long int size = (nbSol/omp_get_max_threads()); //Taille de matrice que chaque Thread doit traiter
	
	#pragma omp parallel for reduction(+:satisfiable) //On parallèlise la génération et le test de toutes les matrices
	for(int numThread=0; numThread<omp_get_max_threads(); numThread++) {
		unsigned long long int begin, end;
		begin = size*numThread;
		end = begin+size;
		
		std::vector<bool> mat(n*q);
		conv(mat,begin);
		
		for(unsigned long long int k=begin; k<end; ++k) {
			bool tmp = true;
			for(unsigned int i=0; i < contraintes.size(); ++i) {
				tmp = contraintes[i](mat, n, q);
				if(!tmp)
					break;
			}
		
			satisfiable+=tmp;

			for(int i=mat.size()-1; i >= 0; --i) {
				if(mat[i]) {
					mat[i] = false;
				} else {
					mat[i] = true;
					break;
				}
			}
		}
	
	}
	
	std::cout << satisfiable << std::endl;

	return satisfiable;
}

int main(int argc, char **argv) {
	int n = 0;
	int q = 0;
	for(int i=1; i < argc; ++i) {
		if(std::string(argv[i]) == "-n") {
			n = std::stoi(argv[i+1]);
		} else if(std::string(argv[i]) == "-q") {
			q = std::stoi(argv[i+1]);
		}
	}

	if(solve(n,q,{&contrainte1, &contrainte2})>0) {
		std::cout << "C'est satisfiable" << std::endl;
	} else {
		std::cout << "C'est insatisfiable" << std::endl;
	}

	return 0;
}
