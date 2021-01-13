#include <iostream>

using namespace std;

class base{
public:
    explicit base(int age = 0) : m_age(age){
        cout << "base class constructor created" << endl;
    };

    virtual ~base(){
        cout << "base class deconstructor deleted" << endl;
    };

    int get_age(){
        return this->m_age;
    }

    void set_age(const int& age){
        this->m_age = age;
    }

    virtual void print(){
        cout << "The base class: " + to_string(this->get_age()) << endl;
    }
private:
    int m_age;
};

class derived : public virtual base{
public:
    derived(int age, string name = "") : base(age), m_name(name){
        cout << "derived class constructor created" << endl;
    }

    virtual ~derived(){
        cout << "derived class deconstructor deleted" << endl;
    }

    int get_age(){
        return base::get_age();
    }

    void set_age(const int& age){
        base::set_age(age);
    }

    string get_name(){
        return this->m_name;
    }

    void set_name(const string& name){
        this->m_name = name;
    }

    void print() override{
        cout << "The derived class: " + to_string(get_age()) + " , " + get_name()<< endl;
    }
private:
    string m_name;
};

void PrintName(base* entity){
    entity->print();
}

int main(){

    base* jie = new base();
    PrintName(jie);

//    delete jie;

    derived* yang = new derived(12, "yang jie");
    PrintName(yang);

//    delete yang;

    return 0;
}
