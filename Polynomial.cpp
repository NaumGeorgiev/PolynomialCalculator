#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Polynomial
{
private:
    vector<pair<int, int>> coefficients;

public:
    Polynomial(const vector<pair<int, int>> &coefficients)
    {
        this->coefficients = coefficients;
    }

    // vector<pair<int, int>> getCoefficients()
    // {
    //     return this->coefficients;
    // }

    // int higher(const int &a, const int &b)
    // {
    //     if (a > b)
    //         return a;
    //     return b;
    // }

    // pair<int, int> getCoefficientAt(int index)
    // {
    //     if (coefficients.size() > index)
    //         return coefficients[index];
    //     return {0, 1};
    // }

    // Polynomial add(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = higher(thisSize, otherSize);
    //     vector<pair<int, int>> sum(size);

    //     for (int i = 0; i < size; i++)
    //         sum[i] = getCoefficientAt(i) + other.getCoefficientAt(i);

    //     return Polynomial(sum);
    // }

    // Polynomial subtract(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = higher(thisSize, otherSize);
    //     vector<pair<int, int>> difference(size);

    //     for (int i = 0; i < size; i++)
    //         difference[i] = getCoefficientAt(i) - other.getCoefficientAt(i);
    //     return Polynomial(difference);
    // }

    // double sum(const double &a, const double &b)
    // {
    //     return a + b;
    // }

    // Polynomial multiply(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = thisSize + otherSize - 1;
    //     vector<pair<int, int>> product(size);

    //     for (int i = 0; i < thisSize; i++)
    //         for (int j = 0; j < otherSize; j++)
    //             product[i + j] += getCoefficientAt(i) * other.getCoefficientAt(j);
    //     return Polynomial(product);
    // }

    //  Polynomial divide(Polynomial &other)
    // {
    //     vector<pair<int, int>> otherCoefficients = other.getCoefficients();
    //     int thisSize = coefficients.size();
    //     int otherSize = otherCoefficients.size();

    //     int size = thisSize - otherSize + 1;
    //     vector<pair<int, int>> quotient(size);

    //     return Polynomial(quotient);
    // }
    //
    // void print()
    // {
    //     for (int i = 0; i < coefficients.size(); i++)
    //     {
    //         if (i == 0)
    //             cout << coefficients[i] << ' ';
    //         else if (i == 1)
    //             cout << coefficients[i] << 'x' << ' ';
    //         else
    //             cout << coefficients[i] << 'x' << '^' << i << ' ';
    //         if (i != coefficients.size() - 1)
    //             cout << '+' << ' ';
    //         else
    //             cout << endl;
    //     }
    // }
};

vector<vector<char>> getSplitCoefficients(vector<char> input)
{
    vector<vector<char>> splitCoefficients;
    vector<char> coefficients;
    for (int i = 0; i <= input.size(); i++)
    {
        if (input[i] == ',' || i == input.size())
        {
            splitCoefficients.push_back(coefficients);
            coefficients.clear();
        }
        else
            coefficients.push_back(input[i]);
    }
    return splitCoefficients;
}

vector<char> getNumerator(vector<char> coefficient)
{
    vector<char> numerator;
    for (int i = 0; coefficient[i] != '\0' && coefficient[i] != '/'; i++)
        numerator.push_back(coefficient[i]);
    return numerator;
}
vector<char> getDenominator(vector<char> coefficient)
{
    int start = 0;
    for (int i = 0; coefficient[i] != '\0'; i++)
    {
        start++;
        if (coefficient[i] == '/')
            break;
    }

    vector<char> denominator;
    for (int i = start; coefficient[i] != '\0'; i++)
        denominator.push_back(coefficient[i]);
    return denominator;
}

int getDecimalDigitCount(vector<char> number)
{
    int startingIndex = 1;
    while (number[startingIndex - 1] != '\0' && number[startingIndex - 1] != '.')
        startingIndex++;
    int count = 0;
    for (int i = startingIndex; number[i] != '\0'; i++)
        count++;

    return count;
}

int smaller(const int &a, const int &b){
    if(a < b)
        return a;
    return b;
}

// void removeDecimalPoint(vector<char> &numerator, vector<char> &denominator){
//     int numeratorDecimalDigitCount = getDecimalDigitCount(numerator);
//     int denominatorDecimalDigitCount = getDecimalDigitCount(denominator);
//     int smaller
    
// }

// pair<int, int> toFraction(vector<char> coefficient)
// {
//     pair<int, int> fraction;
//     vector<char> numerator = getNumerator(coefficient);
//     vector<char> denominator = getDenominator(coefficient);


    
// }

void startLoop()
{
    cout << "give polynomial" << endl;
    vector<char> input = {'2', '.', '5', '4', '/', '4', '.', '3', ',', '3', '.', '1', '4'};
    vector<vector<char>> splitCoefficients = getSplitCoefficients(input);

    for (int i = 0; i < splitCoefficients.size(); i++)
    {
        for (int j = 0; j < splitCoefficients[i].size(); j++)
        {
            cout << splitCoefficients[i][j];
        }
        cout << endl;
    }
    smaller(3, 2);
    vector<char> denominator = getDenominator(splitCoefficients[0]);
    for (int i = 0; i < denominator.size(); i++)
        cout << denominator[i];
    // vector<pair<int, int>> polynomial;
    // for (int i = 0; i < splitCoefficients.size(); i++)
    //     polynomial.push_back(toFraction(splitCoefficients[i]))

    /*
    vector<vector<char>> parts = {2.54/4.3}, {3.5}, {9}
    for each
    vector<char> numerator = 2.54
    numeratorDecimalDigitsCount = 2

    vector<char> denominator = 4.3
    denominatorDecimalDigitsCount = 1

    pair<int, int> toFraction(vector<char> numerator, numeratorDigitsCOunt, ...)
     */
}

int main()
{
    startLoop();
    return 0;
}
