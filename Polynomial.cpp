#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Polynomial
{
private:
    vector<int> coefficients;

public:
    Polynomial(const vector<int> &coefficients)
    {
        this->coefficients = coefficients;
    }

    vector<int> getCoefficients()
    {
        return this->coefficients;
    }

    int smaller(const int &a, const int &b)
    {
        if (a < b)
            return a;
        return b;
    }
    vector<int> add(Polynomial &other)
    {
        vector<int> sum;
        int size = smaller(coefficients.size(), other.getCoefficients().size());
        sum.resize(size);

        for (int i = 0; i < size; i++)
            sum[i] = coefficients[i] + other.getCoefficients()[i];
        return sum;
    }

    vector<int> substract(Polynomial &other)
    {
        other.getCoefficients()[2] = 1;
        vector<int> difference;
        int size = smaller(coefficients.size(), other.getCoefficients().size());
        difference.resize(size);

        for (int i = 0; i < size; i++)
            difference[i] = coefficients[i] - other.getCoefficients()[i];
        return difference;
    }

    void print()
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            if (i == 0)
                cout << coefficients[i] << ' ';
            else if (i == 1)
                cout << coefficients[i] << 'x' << ' ';
            else
                cout << coefficients[i] << 'x' << '^' << i << ' ';
            if (i != coefficients.size() - 1)
                cout << '+' << ' ';
            else
                cout << endl;
        }
    }
};
int main()
{
    Polynomial p1({1, 2, 3});
    Polynomial p2({1, 2, 3});

    Polynomial sum = p1.add(p2);
    Polynomial difference = p1.substract(p2);

    p1.print();
    sum.print();
    difference.print();

    return 0;
}