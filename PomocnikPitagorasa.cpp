// PomocnikPitagorasa.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <math.h>

int calculateTheFristNumber(std::string _birthDate);
int calculateTheSecondNumber(std::string _birthDate);
int calculateTheThirdNumber(std::string _birthDate);
int calculateTheFourthNumber(std::string _birthDate);
int extractCharFromPosition_getTheNumber(std::string _birthDate, int _position);
int seekAndCount(int _number, int _target);

int main()
{
    std::string m_birthDate;
    std::cout << "Za chwile wprowadzisz date urodzenia." << std::endl;
    std::cout << "Zostana wyliczone wartosci robocze" << std::endl;
    std::cout << "opisane w ksiazce 'Numerologiczny kwadrat Pitagorasa'." << std::endl;
    std::cout << "Interpretacja tych wartosci nalezy do ciebie..." << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Podaj date urodzenia w formacie Dzien.Miesiac.Rok - przyklad 03.11.2021.\n !! Prosze nie pomijac zer. W 'metodzie' wazna jest kazda cyfra." << std::endl;
    std::cin >> m_birthDate;
    std::cout << "=====================================" << std::endl;
    std::cout << "Pierwsza liczba robocza: " << calculateTheFristNumber(m_birthDate) << std::endl;
    std::cout << "Druga liczba robocza: " << calculateTheSecondNumber(m_birthDate) << std::endl;
    std::cout << "Trzecia liczba robocza: " << calculateTheThirdNumber(m_birthDate) << std::endl;
    std::cout << "Czwarta liczba robocza: " << calculateTheFourthNumber(m_birthDate) << std::endl;
    std::cout << "=====================================" << std::endl;
    
    for (int i = 0; i <= 10; i++)
    {
        int tmp = 0; //Zliczamy wystapienia danej cyfry w dacie, i kazdej liczbie roboczej

        tmp = tmp + seekAndCount(calculateTheFristNumber(m_birthDate), i);
        tmp = tmp + seekAndCount(calculateTheSecondNumber(m_birthDate), i);
        tmp = tmp + seekAndCount(calculateTheThirdNumber(m_birthDate), i);
        tmp = tmp + seekAndCount(calculateTheFourthNumber(m_birthDate), i);

        int tmp_day, tmp_month;
        tmp_day = extractCharFromPosition_getTheNumber(m_birthDate, 0) * 10 + extractCharFromPosition_getTheNumber(m_birthDate, 1);
        tmp_month = extractCharFromPosition_getTheNumber(m_birthDate, 3) * 10 + extractCharFromPosition_getTheNumber(m_birthDate, 4);

        
        int start = 0;
        if (tmp_day == 10)
        {///Jesli dzien to 10 to szukamy naszego targetu w miesiacach i roku
            start = 2;
            //jezeli w aktualnym obiegu szukamy liczby 10 to
            if (i == 10)
            {
                tmp = tmp + 1;
            }
        }
        if (tmp_month == 10)
        {///Jesli dzien to 10 to szukamy naszego targetu w miesiacach i roku
            start = 6;
            if (i == 10)
            {
                tmp = tmp + 1;
            }
        }

        for (int j = start; j < 10; j++)
        {
            tmp = tmp + seekAndCount(extractCharFromPosition_getTheNumber(m_birthDate,j), i);
            
        }

        std::cout << "Ilosc " << i << " wynosi " << tmp << std::endl;
    }
    std::cout << "=====================================" << std::endl;
    std::cout << "Ilosc cyfr nie bedacych zerem w dacie urodzenia wynosi ";
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        if (extractCharFromPosition_getTheNumber(m_birthDate, i) > 0)count++;
    }
    std::cout << count <<  std::endl;

}
int extractCharFromPosition_getTheNumber(std::string _birthDate, int _position)
{
    char _theLtetter;
    int _number;
    /// Pozyskuje ze lancucha znaków pojedynczy symbol i stara się go przekonwerować na liczbe. Zgodnie z tabela ASCII dla 
    /// 0 zwraca 0 dla 1 zwraca 1 dla 2 zwraca 2 ... dla 9 zwraca 9. Dla symbolu '.' zwraca liczbe "-2"
    /// 
    /// </summary>
    /// <param name="_birthDate"></param>
    /// <param name="_position"></param>
    /// Funkcja zwraca liczbe -2 jeżeli napotka kropke
    if (_position > _birthDate.size())
    {
        std::cerr << "Funkcja extractCharFromPosition_getTheNumber probuje odczytać " << _position << " znak. Data urodzenia liczy zaś tylko " << _birthDate << " znakow. Aplikacja zostanie zamknieta." << std::endl;
        exit(487);
    }


    _theLtetter = _birthDate[ _position ];

    //Konwersja znaku ASCII na cyfre.
    // https://pl.wikipedia.org/wiki/ASCII
    _number = int(_theLtetter) - 48;
    //Jeżeli liczbą do wyłuskania jest separator kropki uznajemy że funkcja zwraca 0; zatem
    if (_number == -2)return -2;

    if ((_number >= 0 && _number <= 9))return _number;
    else
    {
        std::cerr << "Funkcja extractCharFromPosition_getTheNumber probuje odczytac' " << _birthDate[_position] << " ' znak i przekonwertowac go na liczbe. Aplikacja zostanie zamknieta." << std::endl;
        exit(13);
    }

}
int calculateTheFristNumber(std::string _birthDate)
{
    int sum = 0;

    //Liczba 10 jest trktowana jako 10 nie zas jako 1+ 0;
    int tmp_day = extractCharFromPosition_getTheNumber(_birthDate, 0) * 10 + extractCharFromPosition_getTheNumber(_birthDate, 1);
    int tmp_month = extractCharFromPosition_getTheNumber(_birthDate, 3) * 10 + extractCharFromPosition_getTheNumber(_birthDate, 4);

    int start = 0;
    if (tmp_day == 10)
    {
        start = 3; sum = sum + 10;
    }
    if (tmp_month == 10)
    {
        start = 5; sum = sum + 10;
    }
    for (int  i = start; i < _birthDate.size() ;i++)
    {
        sum = sum + extractCharFromPosition_getTheNumber(_birthDate, i);
        if (extractCharFromPosition_getTheNumber(_birthDate, i) == -2)sum = sum + 2;
    }
    return sum;
}
int calculateTheSecondNumber(std::string _birthDate)
{
    int _number = calculateTheFristNumber(_birthDate);



    return  (_number % 10) + ((_number / 10) % 10);
}
int calculateTheThirdNumber(std::string _birthDate)
{
    int _firstNumber = calculateTheFristNumber(_birthDate);
    int _birthDateToNumber = 0;

    _birthDateToNumber = extractCharFromPosition_getTheNumber(_birthDate, 0);
    if(_birthDateToNumber == 0)_birthDateToNumber = extractCharFromPosition_getTheNumber(_birthDate, 1);///w dacie 01.01.1998 pierwsze jest zero które musimy odrzucic

    return _firstNumber - (2 * _birthDateToNumber);
}
int calculateTheFourthNumber(std::string _birthDate)
{
    int _number = calculateTheThirdNumber(_birthDate);



    return  (_number % 10) + ((_number / 10) % 10);
}
int seekAndCount(int _number, int _target)
{
    int count = 0;

    do
    {
        if (_number % 10 == _target)count++;
        _number = _number / 10;

        if (_number == 0)break;

    } while ( 1 );

    return count;
}