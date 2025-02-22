#include <bits/stdc++.h>
using namespace std;

class CarInterface
{
public:
    virtual int getTopSpeed() = 0;
    virtual ~CarInterface() {}
};

class EconomicCar1 : public CarInterface
{
public:
    int getTopSpeed() override
    {
        return 120;
    }
};

class EconomicCar2 : public CarInterface
{
public:
    int getTopSpeed() override
    {
        return 150;
    }
};

class LuxuryCar1 : public CarInterface
{
public:
    int getTopSpeed() override
    {
        return 180;
    }
};
class LuxuryCar2 : public CarInterface
{
public:
    int getTopSpeed() override
    {
        return 250;
    }
};

class AbstractFactoryInterface
{
public:
    virtual CarInterface *getInstance(int price) = 0;
    virtual ~AbstractFactoryInterface() {}
};

class EconomicCarFactory : public AbstractFactoryInterface
{
public:
    CarInterface *getInstance(int price)
    {
        if (price <= 3000000)
        {
            return new EconomicCar1();
        }
        else if (price > 3000000 && price <= 4000000)
        {
            return new EconomicCar2();
        }
        return NULL;
    }
};

class LuxuryCarFactory : public AbstractFactoryInterface
{
public:
    CarInterface *getInstance(int price)
    {
        if (price > 4000000 && price <= 8000000)
        {
            return new LuxuryCar1();
        }
        else if (price > 8000000)
        {
            return new LuxuryCar2();
        }
        return NULL;
    }
};

class AbstractFactoryProducer
{
public:
    AbstractFactoryInterface *getFactoryInstance(string value)
    {
        if (value == "LUXURY")
        {
            return new LuxuryCarFactory();
        }
        else if (value == "ECONOMIC")
        {
            return new EconomicCarFactory();
        }
        return NULL;
    }
};

int main()
{
    AbstractFactoryProducer *absFactoryProducer = new AbstractFactoryProducer();
    AbstractFactoryInterface *absFactoryObj = absFactoryProducer->getFactoryInstance("LUXURY");
    CarInterface *c1 = absFactoryObj->getInstance(7800000);
    cout << c1->getTopSpeed() << endl;
    CarInterface *c2 = absFactoryObj->getInstance(15000000);
    cout << c2->getTopSpeed() << endl;

    absFactoryObj = absFactoryProducer->getFactoryInstance("ECONOMIC");
    c1 = absFactoryObj->getInstance(300000);
    c2 = absFactoryObj->getInstance(3450000);
    cout << c1->getTopSpeed() << endl;
    cout << c2->getTopSpeed() << endl;

    delete c1;
    delete c2;
}