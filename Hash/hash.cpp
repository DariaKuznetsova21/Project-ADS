#include <iostream>
#include <string>

#define N 300

using namespace std;

class Identifier
{
private:
    Identifier* next;
    string name;
    string surname;
    int position;

public:
    Identifier(const string& somename, const string& sur);
    ~Identifier();

    Identifier* get_next();
    void set_next(Identifier* nx);
    string get_name();
    string get_surname();
    int get_position();
    void set_position(const int n);
};

Identifier::Identifier(const string& somename, const string& sur)
{
    name = somename;
    surname = sur;
    next = NULL;
    position = 0;
}

Identifier::~Identifier()
{}

int Identifier::get_position()
{
    return position;
}

void Identifier::set_position(const int n)
{
    position = n;
}

Identifier* Identifier::get_next()
{
    return next;
}

void Identifier::set_next(Identifier* nxt)
{
    next = nxt;
}

string Identifier::get_name()
{
    return name;
}

string Identifier::get_surname()
{
    return surname;
}

class HashTable
{
private:
    Identifier* table[N]{};


public:
    HashTable() {} //����������� �� ���������
    ~HashTable(); //����������

    bool add(const string& name, const string& surname); //���������� �������� � �������
    bool delElem(const string& name, const string& surname);
    Identifier* find(const string& name, const string& surname); //����� ��������

    static int hash(const string& name)
    {
        auto ascii = 0;

        for (char nam : name)
        {
            ascii += nam * 31;
        } //�������� ����

        return (ascii % N + (1 + ascii % (N - 2))) % N;//������� 3-�� ��������
    }
};

HashTable::~HashTable() //����������
{
    for (int i = 0; i < N; ++i)
    {
        if (table[i]) {
            delete table[i];
            table[i] = nullptr;
        }
    }
}

bool HashTable::add(const string& name, const string& surname) //���������� �������� � �������
{
    const int hashNumber = hash(name);//���������� ������� �����������

    Identifier* iden = new Identifier(name, surname);//������ ������� �������

    //���� ������ ������� �� ������������ ���-����� 
    Identifier* place = table[hashNumber];

    if (place == nullptr) //���� ������ ��������, ��������� �
    {
        iden->set_position(hashNumber);
        table[hashNumber] = iden;
        return true;
    }
    bool isEmptyRowFound = false;

    //����� ��������� ��������
    //���� ������ ������ ������ � �������
    for (int i = 0; i < N && !isEmptyRowFound; ++i) {
        if (table[i] == nullptr) {
            iden->set_position(i);
            table[i] = iden;
            isEmptyRowFound = true;
        }
    }

    if (isEmptyRowFound) {
        //��������� ��������� � ���������� �������(� ����� ������)
        for (; place->get_next() != nullptr; place = place->get_next());
        place->set_next(iden);
        return true;
    }
    else {
        delete iden;
        return false;
    }
}

bool HashTable::delElem(const string& name, const string& surname) //�������� ��������
{
    const int hashNumber = hash(name);//��������� ���

    Identifier* result = table[hashNumber];//���� ������� �� �������

    if (result == nullptr)//���� ������ ��c��, ������ �������� �������� ���
    {
        return false;
    }

    //���� �� �� ��������� ������� ������, ��� �� ������
    for (; (result->get_name() != name) || (result->get_surname() != surname); result = result->get_next())
    {
        if (result->get_next() == nullptr)//���� ��� ��� � ������, ��� ��� � �������
        {
            return false;
        }
    }

    if (result->get_next()) {
        string name = result->get_next()->get_name();
        string surname = result->get_next()->get_surname();
        int index = result->get_next()->get_position();
        table[index] = NULL;
        
        table[result->get_position()] = NULL;
        this->add(name, surname);
        Identifier* newId = this->find(name, surname);
        table[newId->get_position()]->set_next(result->get_next());
    }
    else
        table[result->get_position()] = NULL;
    
    delete result;
    result = NULL;
    
    return true;
}

Identifier* HashTable::find(const string& name, const string& surname) //����� ��������
{
    const int hashNumber = hash(name);//��������� ���

    Identifier* result = table[hashNumber];//���� ������� �� �������
    if (result->get_name() == name && result->get_surname() == surname)
    {
        return result;
    }
    while (result->get_next() != nullptr)
    {
        result = result->get_next();
        if (result->get_name() == name && result->get_surname() == surname)
        {
            return result;
        }
    }
    return nullptr;
}

int main()
{
    /*HashTable table;

    for (int i = 0; i < N; ++i)
    {
        cout << "Name and surname the object: ";

        string name;
        string surname;

        cin >> name >> surname;

        table.add(name, surname);

        cout << "Do you want continue? Any / N" << endl;
        char choose;

        cin >> choose;

        if (choose == 'N' || choose == 'n')
        {
            break;
        }
    }

    Identifier* iden = table.find("Daria", "Kuznetsova");

    if (iden)
    {
        cout << "Name '" << iden->get_name() << "' with surname '" << iden->get_surname() <<
        "' was found" << endl;
    }

    iden = table.find("Evgenii", "Zudilov");

    if (iden)
    {
        cout << "Name '" << iden->get_name() << "' with surname '" << iden->get_surname() <<
        "' was found" << endl;
    }

    table.delElem("Daria", "Kuznetsova");

    iden = table.find("name", "sur");
    if (iden)
    {
        cout << "Name '" << iden->get_name() << "' with surname '" << iden->get_surname() <<
        "' was found" << endl;
    }*/

    HashTable test;
    test.add("a", "b");
    test.add("a", "c");
    test.add("a", "d");

    test.delElem("a", "b");
    cout<<test.find("a", "c")->get_name()<<endl;
    cout << test.find("a", "d")->get_name() << endl;
    return 0;
}