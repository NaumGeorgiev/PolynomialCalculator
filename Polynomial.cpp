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

    int higher(const int &a, const int &b)
    {
        if (a > b)
            return a;
        return b;
    }

    int getCoefficientAt(int index)
    {
        if (coefficients.size() > index)
            return coefficients[index];
        return 0;
    }

    Polynomial add(Polynomial &other)
    {
        vector<int> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = higher(thisSize, otherSize);
        vector<int> sum(size);

        for (int i = 0; i < size; i++)
            sum[i] = getCoefficientAt(i) + other.getCoefficientAt(i);

        return Polynomial(sum);
    }

    Polynomial subtract(Polynomial &other)
    {
        vector<int> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = higher(thisSize, otherSize);
        vector<int> difference(size);

        for (int i = 0; i < size; i++)
            difference[i] = getCoefficientAt(i) - other.getCoefficientAt(i);
        return Polynomial(difference);
    }

    int sum(const int &a, const int &b)
    {
        return a + b;
    }

    Polynomial multiply(Polynomial &other)
    {
        vector<int> otherCoefficients = other.getCoefficients();
        int thisSize = coefficients.size();
        int otherSize = otherCoefficients.size();

        int size = thisSize + otherSize - 1;
        vector<int> product(size);

        for (int i = 0; i < thisSize; i++)
            for (int j = 0; j < otherSize; j++)
                product[i + j] += getCoefficientAt(i) * other.getCoefficientAt(j);
        return Polynomial(product);
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
    Polynomial p1({1, 0, 0, 0});
    Polynomial p2({1, 2, 3});
    Polynomial sum = p1.add(p2);
    Polynomial difference = p1.subtract(p2);
    Polynomial product = p1.multiply(p2);

    p1.print();
    p2.print();
    product.print();

    return 0;
}