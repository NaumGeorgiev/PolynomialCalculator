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

void simplify(pair<int, int> &fraction)
{
    int gcd = findGCD(fraction.first, fraction.second);
    fraction.first /= gcd;
    fraction.second /= gcd;
}

pair<int, int> addFractions(pair<int, int> a, pair<int, int> b)
{
    rewriteWithCommonDenominators(a, b);
    pair<int, int> sum;
    sum.first = a.first + b.first;
    sum.second = a.second;
    simplify(sum);
    return sum;
}

pair<int, int> subtractFractions(pair<int, int> a, pair<int, int> b)
{
    rewriteWithCommonDenominators(a, b);
    pair<int, int> difference;
    difference.first = a.first - b.first;
    difference.second = a.second;
    simplify(difference);
    return difference;
}

pair<int, int> multiplyFractions(pair<int, int> a, pair<int, int> b)
{
    pair<int, int> product;
    product.first = a.first * b.first;
    product.second = a.second * b.second;
    simplify(product);
    return product;
}

pair<int, int> divideFractions(pair<int, int> a, pair<int, int> b)
{
    pair<int, int> quotient;
    quotient.first = a.first * b.second;
    quotient.second = a.second * b.first;
    simplify(quotient);
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
        return pair{0, 1};
    }

    Polynomial operateWith(Polynomial other, char function)
    {
        int thisSize = coefficients.size();
        int otherSize = other.getCoefficients().size();
        int higherSize = max(thisSize, otherSize);

        vector<pair<int, int>> summedCoefficients;
        for (int i = 0; i < higherSize; i++)
        {
            pair<int, int> thisValue = getCoefficientAt(i);
            pair<int, int> otherValue = other.getCoefficientAt(i);
            if (function == '+')
                summedCoefficients.push_back(addFractions(thisValue, otherValue));
            else if (function == '-')
                summedCoefficients.push_back(subtractFractions(thisValue, otherValue));
        }
        return Polynomial(summedCoefficients);
    }

    Polynomial add(Polynomial &other)
    {
        return operateWith(other, '+');
    }

    Polynomial subtract(Polynomial &other)
    {
        return operateWith(other, '-');
    }

    Polynomial multiply(Polynomial &other)
    {
        int thisSize = coefficients.size();
        int otherSize = other.getCoefficients().size();
        vector<pair<int, int>> multipliedCoefficients(thisSize + otherSize - 1);
        for (int i = 0; i < multipliedCoefficients.size(); i++)
            multipliedCoefficients[i] = {0, 1};
        for (int i = 0; i < coefficients.size(); i++)
            for (int j = 0; j < other.coefficients.size(); j++)
            {
                pair<int, int> thisValue = getCoefficientAt(i);
                pair<int, int> otherValue = other.getCoefficientAt(j);
                pair<int, int> multipliedValue = multiplyFractions(thisValue, otherValue);
                multipliedCoefficients[i + j] = addFractions(multipliedCoefficients[i + j], multipliedValue);
            }
        return Polynomial(multipliedCoefficients);
    }

    pair<int, int> powFraction(pair<int, int> fraction, int n)
    {
        fraction.first = pow(fraction.first, n);
        fraction.second = pow(fraction.second, n);
        return fraction;
    }

    pair<int, int> valueForX(pair<int, int> x)
    {
        pair<int, int> value = {0, 1};
        for (int i = 0; i < coefficients.size(); i++)
            value = addFractions(value, multiplyFractions(powFraction(x, i), coefficients[i]));
        return value;
    }

    Polynomial multiply(pair<int, int> factor)
    {
        for (int i = 0; i < coefficients.size(); i++)
            coefficients[i] = multiplyFractions(coefficients[i], factor);
        return Polynomial(coefficients);
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

vector<char> polynomialInput()
{
    vector<char> input;
    char symbol;
    cin >> symbol;
    while (symbol != 's')
    {
        input.push_back(symbol);
        cin >> symbol;
    }
    return input;
}

Polynomial askForPolynomial()
{
    vector<char> input = polynomialInput();
    vector<pair<int, int>> coefficients = parseCoefficients(input);
    for (int i = 0; i < coefficients.size(); i++)
        simplify(coefficients[i]);
    return Polynomial(coefficients);
}

void startLoop()
{
    cout << "give polynomial" << endl;
    Polynomial firstPolynomial = askForPolynomial();
    // Polynomial secondPolynomial = askForPolynomial();

    firstPolynomial.print();

    // pair<int, int> value = firstPolynomial.valueForX(pair{2.5, 1});
    // cout << value.first << '/' << value.second;

    // Polynomial summedPolynomial = firstPolynomial.add(secondPolynomial);
    // Polynomial subtractedPolynomial = firstPolynomial.subtract(secondPolynomial);
    // Polynomial multipliedPolynomial = firstPolynomial.multiply(secondPolynomial);
    // Polynomial dividedPolynomial = firstPolynomial.divide(secondPolynomial);

    // Polynomial summedPolynomial = firstPolynomial.add(secondPolynomial);
    // Polynomial summedPolynomial = firstPolynomial.add(secondPolynomial);
    // vector<char> factor = {'7','.','5','/','1'};
    // Polynomial factored = firstPolynomial.multiply(pair{parseCoefficient(factor)});
    // factored.print();
    // summedPolynomial.print();
    // subtractedPolynomial.print();
    // multipliedPolynomial.print();
    // dividedPolynomial.print();

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
    startLoop();

    return 0;
}
