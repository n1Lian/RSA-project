#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;

bool checkPrime (long int nunmber);
long int gcd (long int a, long int b);
long int findE (long int m);
long int findD(long int e, long int m);
long int encrypt (long int i, long int e, long int n);
long int decrypt (long int i, long int d, long int n);

int main()
{
	long int p, q, n, m, e, d;
	long int message[100] = { 0 }, ciphertext[100] = { 0 };
	string mainText;
	bool flag;

	// Cоздание открытого и секретного ключей
	// 1. Выбираются два больших простых числа p и q;

	do
	{
		cout << "Enter a first prime number:" << endl;
		cin >> p;
		flag = checkPrime(p);

		if (flag == false)
		{
			cout << "\nIt`s not a prime number. Prime numbers are special numbers, greater than 1, that have exactly two factors, themselves and 1";
		}
	} while (flag == false);

	do
	{
		cout << "Enter a second prime number:" << endl;
		cin >> q;
		flag = checkPrime(q);

		if (flag == false)
		{
			cout << "\nIt`s not a prime number. Prime numbers are special numbers, greater than 1, that have exactly two factors, themselves and 1";
		}
	} while (flag == false);
	// 2. Вычисляется: n = p ⋅ q
	n = p * q;
	// m = (p – 1) ⋅ (q – 1)
	m = (p - 1) * (q - 1);
	// 3. Определяется  такое число e, для которого является истинным выражение : (e ⋅ d) mod(m) = 1
	e = findE(m);
	// 4. Выбирается случайное число d, взаимно простое с m 
	d = findD(e, m);
	// 5. Числа e и n – это открытый ключ, а числа d и n – это закрытый ключ
	cout << "{e, n} = " << e << ", " << n << " - public key" << endl;
	cout << "{d, n} = " << d << ", " << n << " - private key" << endl;

	cout << "\nEnter your message:" << endl;
	cin.ignore();
	getline(cin, mainText);
	cout << "\nThe message is: " << mainText << endl;

	// Шифрование:
	// 1. Исходный текст разбивается на блоки
	// 2. Зашифровка

	for (long int i = 0; i < mainText.length(); i++)
	{
		message[i] = encrypt(mainText[i], e, n);
	}

	std::cout << "\nTHE ENCRYPTED MESSAGE IS:" << std::endl;

	for (long int i = 0; i < mainText.length(); i++)
	{
		printf("%c", (char)message[i]);
	}

	// 3. Дешифровка

	for (long int i = 0; i < mainText.length(); i++)
	{
		ciphertext[i] = decrypt(message[i], d, n);
	}

	std::cout << "\n\nTHE DECRYPTED MESSAGE IS:" << std::endl;

	for (long int i = 0; i < mainText.length(); i++)
	{
		printf("%c", (char)ciphertext[i]);
	}
	return 0;
}

bool checkPrime(long int number)
{
	for (int i = 2; i < number; i++)
	{
		if (number % i == 0)
			return false;
	}
	return true;
}

long int gcd(long int a, long int b) // Функция нахлждения НОД, нужна для поиска -е-
{
	while (a > 0)
	{
		long int res;

		res = a;
		a = b % a;
		b = res;
	}

	return b;
}

long int findE (long int m)
{
	long int e;

	for (e = 2; e < m; e++)
	{
		if (gcd(e, m) == 1)
			return e;
	}

	return 0;
}

long int findD(long int e, long int m)
{
	// Вычисляется число d, мультипликативно обратное к числу e по модулю ф(n), то есть число, удовлетворяющее сравнению:
	//    d*e = 1 (mod ф(n))

	long int d;
	long int k = 1;

	while (1)
	{
		k = k + m;

		if (k % e == 0)
		{
			d = (k / e);
			return d;
		}
	}

}

long int encrypt(long int i, long int e, long int n)
{
	// Шифрование текста выполняется следующим образом: C(i) = (M(i)^e) mod n
	long int current, result;

	current = i;
	result = 1;

	for (long int j = 0; j < e; j++)
	{
		result = result * current;
		result = result % n;
	}

	return result;
}

long int decrypt(long int i, long int d, long int n)
{
	// Расшифрование сообщения выполняется следующим образом: M(i) = (C(i)^d) mod n
	long int current, result;

	current = i;
	result = 1;

	for (long int j = 0; j < d; j++)
	{
		result = result * current;
		result = result % n;
	}

	return result;
}
