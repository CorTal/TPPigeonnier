#include <iostream>
#include <string>
#include <vector>

typedef bool (*CONSTRAINT) (const std::vector<bool>& mat, int n, int q);

bool constraint1(const std::vector<bool>& mat, int n, int q)
{
	for(int i(0); i < n; ++i)
	{
		unsigned int tmp = 0;
		for(int j(0); j < q; ++j)
		{
			tmp += mat[i*q+j];
		}

		if(tmp != 1)
			return false;
	}

	return true;
}

bool constraint2(const std::vector<bool>& mat, int n, int q)
{
	for(int i(0); i < q; ++i)
	{
		unsigned int tmp = 0;
		for(int j(0); j < n; ++j)
		{
			tmp += mat[j*q+i];
		}

		if(tmp > 1)
			return false;
	}

	return true;
}

bool isequal(const std::vector<bool>& mat1, const std::vector<bool>& mat2)
{
	bool is = true;

	for(unsigned int i(0); i < mat1.size(); ++i)
	{
		is = (!is || (mat1[i] != mat2[i])) ? false : true;
	}

	return is;
}

bool solve(int n, int q, std::vector<CONSTRAINT> constraints)
{
	std::vector<bool> mat(n*q);
	std::vector<bool> end(n*q);
	for(int i(0); i < (n*q); ++i)
	{
		mat[i] = false;
		end[i] = true;
	}

	bool sat = false;

	while(!isequal(mat,end))
	{
		bool tmp = true;
		for(unsigned int i(0); i < constraints.size(); ++i)
		{
			tmp = constraints[i](mat, n, q);
			if(!tmp)
				break;
		}

		sat = (sat || tmp) ? true : false;

		for(unsigned int i(0); i < mat.size(); ++i)
		{
			if(mat[i])
			{
				mat[i] = false;
			}
			else
			{
				mat[i] = true;
				break;
			}
		}
	}

	return sat;
}

int main(int argc, char **argv)
{
	int n = 0;
	int q = 0;
	for(int i(1); i < argc; ++i)
	{
		if(std::string(argv[i]) == "-n")
		{
			n = std::stoi(argv[i+1]);
		}
		else if(std::string(argv[i]) == "-q")
		{
			q = std::stoi(argv[i+1]);
		}
	}

	std::cout << "Is sat ? " << solve(n,q,{&constraint1, &constraint2}) << std::endl;

	return 0;
}
