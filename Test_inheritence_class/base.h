#ifndef BASE_H
#define BASE_H


class base{
public:
    base(double length = 1.2, double width = 15.2);

    void length(double length){
        m_length = length;
    }
    void width(double width){
        m_width = width;
    }

    double length(){
        return m_length;
    }
    double width(){
        return m_width;
    }

    double tringle();

    ~base();

private:
    double m_length;
    double m_width;
};

#endif // BASE_H
