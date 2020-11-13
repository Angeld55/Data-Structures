
#include <iostream>
#include <string>
using namespace std;

//���1. ������� �� ����� n -> ���� n � ������.

//���2. ������� �� ����� n -> ��������� �� ������ ��������� (! ����������)
// 19 = 19
// 96 = 2*2*2*2*2*3 = 2^5 + 3

// 1400 = 2^3 x 5^2 x 7^1.

//���3. ������� �� ������������� ����� n -> �������� n+1. - ���� ����� � �������� ��������

//  0000..10001 
//        10010
//        10011
//        10100

// 1110101101111
// 1110101110000
             

// ���4. ������� �� ������������ ����� n � ������������� ����� k - n+k, ���� � ����� � �������� ��������.


//��� 5. �������� �� n � k.  n*k  ���� � ����� � �������� ��������.

//��� 6:  ����� ���. ����� �� ��������� �� ��������� ����� ���� ���� �� �������� ������� �� 2-����.
//  10 =  2^1 + 2^3
//  26 = 2^1 + 2^3 + 2^4
// ����������� ���� ���������.

// 26 =  11010
int main()
{
	unsigned int n;
	cin >> n;


	int currentPosition = 0;
	while (n != 0)
	{
		if (n % 2 == 1) //�������� �� ��������� ��� 
		{
			cout << "2^" << currentPosition << " ";
		}
		currentPosition++;
		n >>= 1; //  n /=2;
	}

	

}