#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

using namespace std;

vector<vector<char>> splitByComma(const vector<char> &input)
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

vector<char> getNumerator(const vector<char> &coefficient)
{
    vector<char> numerator;
    for (int i = 0; i < coefficient.size() && coefficient[i] != '/'; i++)
        numerator.push_back(coefficient[i]);
    return numerator;
}
vector<char> getDenominator(const vector<char> &coefficient)
{
    int start = 0;
    for (int i = 0; i < coefficient.size(); i++)
    {
        start++;
        if (coefficient[i] == '/')
            break;
    }
    if (start == coefficient.size())
        return vector{'1'};

    vector<char> denominator;
    for (int i = start; i < coefficient.size(); i++)
        denominator.push_back(coefficient[i]);
    return denominator;
}

int getDecimalDigitCount(const vector<char> &number)
{
    int startingIndex = 0;
    while (startingIndex < number.size() - 1 && number[startingIndex] != '.')
        startingIndex++;
    startingIndex++;
    return number.size() - startingIndex;
}

int toInt(const vector<char> &number)
{
    int result = 0;
    for (int i = 0; i < number.size(); i++)
        if (number[i] != '.')
            result = result * 10 + (number[i] - '0');
    return result;
}

pair<int, int> parseCoefficient(const vector<char> &coefficient)
{
    vector<char> numerator = getNumerator(coefficient);
    vector<char> denominator = getDenominator(coefficient);
    int numeratorDecimalDigitCount = getDecimalDigitCount(numerator);
    const int denominatorDecimalDigitCount = getDecimalDigitCount(denominator);
    const int higher = max(numeratorDecimalDigitCount, denominatorDecimalDigitCount);

    const int convertedNumerator = toInt(numerator);
    const int convertedDenominator = toInt(denominator);

    return pair{convertedNumerator, convertedDenominator};
}

vector<pair<int, int>> parseCoefficients(const vector<char> &input)
{
    const vector<vector<char>> splitCoefficients = splitByComma(input);

    vector<pair<int, int>> convertedCoefficients;
    for (int i = 0; i < splitCoefficients.size(); i++)
        convertedCoefficients.push_back(parseCoefficient(splitCoefficients[i]));
    return convertedCoefficients;
}

int findGCD(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int findLCD(int a, int b)
{
    int gcd = findGCD(a, b);
    return a * b / gcd;
}

void rewriteWithCommonDenominators(pair<int, int> &a, pair<int, int> &b)
{
    int denominatorA = a.second;
    int denominatorB = b.second;
    int lcd = findLCD(denominatorA, denominatorB);
    int multiplicatorA = lcd / denominatorA;
    int multiplicatorB = lcd / denominatorB;

    a.first *= multiplicatorA;
    a.second *= multiplicatorA;
    b.first *= multiplicatorB;
    b.second *= multiplicatorB;
}

pair<int, int> add(pair<int, int> a, pair<int, int> b)
{
    rewriteWithCommonDenominators(a, b);
    pair<int, int> sum;
    sum.first = a.first + b.first;
    sum.second = a.second;
    return sum;
}

pair<int, int> subtract(pair<int, int> a, pair<int, int> b)
{
    rewriteWithCommonDenominators(a, b);
    pair<int, int> difference;
    difference.first = a.first - b.first;
    difference.second = a.second;
    return difference;
}

pair<int, int> multiply(pair<int, int> a, pair<int, int> b)
{
    pair<int, int> product;
    product.first = a.first * b.first;
    product.second = a.second * b.second;
    return product;
}

pair<int, int> divide(pair<int, int> a, pair<int, int> b)
{
    pair<int, int> quotient;
    quotient.first = a.first * b.second;
    quotient.second = a.second * b.first;
    return quotient;
}

class Polynomial
{
private:
    vector<pair<int, int>> coefficients;

public:
    Polynomial(const vector<pair<int, int>> &coefficients)
    {
        this->coefficients = coefficients;
    }

    const vector<pair<int, int>> &getCoefficients()
    {
        return coefficients;
    }

    pair<int, int> getCoefficientAt(int index)
    {
        if (index < coefficients.size())
            return coefficients[index];
        return pair{0, 0};
    }

    void print()
    {

        for (int i = 0; i < coefficients.size(); i++)
        {
            int numerator = coefficients[i].first;
            int denominator = coefficients[i].second;
            if (denominator == 1)
                cout << numerator;
            else
                cout << '(' << numerator << '/' << denominator << ')';
            if (i != 0)
            {
                cout << 'x';
                if (i != 1)
                    cout << '^' << i;
            }
            if (i != coefficients.size() - 1)
                cout << " + ";
        }
        cout << endl;
    }
};

// void simplify(pair<int, int> &fraction)
// {
//     int gcd = findGCD(fraction.first, fraction.second);
//     fraction.first /= gcd;
//     fraction.second /= gcd;
// }

void startLoop()
{
    cout << "give polynomial" << endl;
    vector<char> firstInput = {'3', '.', '1', '4', '/', ',', '1', '/', '3', '4'};
    vector<pair<int, int>> coefficients = parseCoefficients(firstInput);
    Polynomial firstPolynomial(coefficients);
    firstPolynomial.print();

    /*  if 1, 2, 3, 4, 7
     give polynomial
     if 5, 6
     give number
     else do nothing*/
}

int main()
{
    pair<int, int> a = {1, 2};
    pair<int, int> b = {1, 3};

    pair<int, int> sum = add(a, b);
    pair<int, int> diff = subtract(a, b);
    pair<int, int> product = multiply(a, b);
    pair<int, int> quotient = divide(a, b);

    cout << product.first << '/' << product.second << endl;
    cout << quotient.first << '/' << quotient.second << endl;

    cout << diff.first << '/' << diff.second << endl;
    cout << sum.first << '/' << sum.second << endl;
    startLoop();

    return 0;
}
