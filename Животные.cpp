#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>
using namespace std;

void task1_3(multimap<string, string>& main, multimap<string, string>::iterator it, string& key, string& data)
{
    if (key != "" && data != "")
    {
        if (main.find(key) == main.end()) {
            main.insert(pair<string, string>(key, data));
        }
        else 
        {
            int n = 1;
            for (it = main.find(key); it->first == key; it++, n++)
            {
                if (it->second == data)
                {
                    break;
                }
                if (n == main.count(key))
                {
                    main.insert(pair<string, string>(key, data));
                }


            }
        }

    }

}
void task4(multimap<string, int>& main, multimap<string, int>::iterator it, string& key, int& data) 
{
    if (key != "")
    {
        if (main.find(key) == main.end())
        {
            main.insert(pair<string, int>(key, data));
            main.insert(pair<string, int>(key, data));
        }
        else
        {
            it = main.find(key);
            if (data > it->second)
            {
                it->second = data;
            }
            else
            {
                ++it;
                if (data < it->second)
                {
                    it->second = data;
                }
            }
        }
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);  
    string owner;
    string species;
    string name;
    int age = 0;
    multimap<string, string>own_spec;
    map<string, multimap<string, string>>spec_own_name;
    multimap<string, string>name_spec;
    multimap<string, string>::iterator i;
    multimap<string, int>spec_age;
    multimap<string, int>::iterator i1;
    ifstream fin("input.txt");
    while (!fin.eof())
    {
        getline(fin, owner, ',');
        getline(fin, species, ',');
        getline(fin, name, ',');
        fin >> age;
        fin.ignore();
        task1_3(own_spec, i, owner, species);
        task1_3(name_spec, i, name, species);
        task4(spec_age, i1, species, age);
        if (spec_own_name.find(species) == spec_own_name.end())
        {
            spec_own_name[species] = { {owner, name} };
        }
        else
        {
            if (spec_own_name[species].find(owner) == spec_own_name[species].end())
            {
                spec_own_name[species].insert(pair<string, string>(owner, name));
            }
            else
            {
                int k = 1;
                for (i = spec_own_name[species].find(owner); i->first == owner; i++, k++)
                {
                    if (i->second == name)
                    {
                        break;
                    }
                    if (k == spec_own_name[species].count(owner))
                    {
                        spec_own_name[species].insert(pair<string, string>(owner, name));
                    }
                }
            }
        }
    }

    int task;
    while (true)
    {
        system("CLS");
        cout << "1: Количество различных видов животных у каждого владельца.\n";
        cout << "2: Для конкретного вида животного вывести всех его владельцев и клички.\n";
        cout << "3: Количество видов животных, которые носят определённую кличку\n";
        cout << "4: Информацию о возрасте самого старого и самого молодого животного каждого вида.\n";
        cout << "5: Выход\n\n";
        cout << "Введите номер задания: ";
        cin >> task;
        switch (task)
        {
        case 1:
            system("CLS");
            i = own_spec.begin();
            while (i != own_spec.end())
            {
                cout << "владелец: " << i->first << ", количество видов животных: " << own_spec.count(i->first) << endl;
                advance(i, own_spec.count(i->first));
            }

            system("PAUSE");
            break;
        case 2:
            system("CLS");
            cout << "введите вид животного : ";
            cin >> species;
            if (spec_own_name.find(species) == spec_own_name.end()) 
            {
                cout << "проверте ввод(похожих видов нет)" << endl;
            }
            else 
            {
                i = spec_own_name[species].begin();
                while (i != spec_own_name[species].end())
                {
                    cout << i->first << " - ";
                    for (int k = 1; k < spec_own_name[species].count(i->first); i++, k++)
                    {
                        cout << i->second << ", ";
                    }
                    cout << i->second << endl;
                    ++i;
                }
            }

            system("PAUSE");
            break;
        case 3:
            system("CLS");
            cout << "введите кличку животного: ";
            cin >> name;
            cout << name_spec.count(name) << endl;

            system("PAUSE");
            break;
        case 4:
            system("CLS");
            i1 = spec_age.begin();
            while (i1 != spec_age.end())
            {
                cout << i1->first << endl;
                cout << " старший : " << i1->second << endl;
                ++i1;
                cout << " младший : " << i1->second << endl;
                ++i1;
            }
            system("PAUSE");
            break;
        case 5:
            system("CLS");
            exit(0);
        default:
            system("CLS");
            cout << "Некорректный ввод!\n";
            system("PAUSE");
        }
    }
    fin.close();
    return 0;
}
