#include<bits/stdc++.h>
using namespace std;

class BasePizzaInterface {
    public:
        virtual int cost() = 0;
};

class ToppingDecoratorInterface: public BasePizzaInterface {};

class MushroomTop: public ToppingDecoratorInterface {
    public:
        BasePizzaInterface* basePizza;
         MushroomTop(BasePizzaInterface* basePizza) {
            this->basePizza = basePizza;
         }

         int cost() override {
            return this->basePizza->cost() + 50;
         }
};

class CheeseTop: public ToppingDecoratorInterface {
    public:
        BasePizzaInterface* basePizza;
        CheeseTop(BasePizzaInterface* basePizza) {
            this->basePizza = basePizza;
         }

         int cost() override {
            return this->basePizza->cost() + 40;
         }
};

class OliveTop: public ToppingDecoratorInterface {
    public:
        BasePizzaInterface* basePizza;
        OliveTop(BasePizzaInterface* basePizza) {
            this->basePizza = basePizza;
         }

         int cost() override {
            return this->basePizza->cost() + 90;
         }
};

class MargeritaBasePizza: public BasePizzaInterface {
    public:
        int cost() override {
            return 200;
        }
};

class FarmhouseBasePizza: public BasePizzaInterface {
    public:
        int cost() override {
            return 500;
        }
};

class VegDelightBasePizza: public BasePizzaInterface {
    public:
        int cost() override {
            return 300;
        }
};


int main() {
    BasePizzaInterface* pizza1 = new CheeseTop(new FarmhouseBasePizza());
    cout<<pizza1->cost()<<endl;
    BasePizzaInterface* pizza2 = new VegDelightBasePizza();
    cout<<pizza2->cost()<<endl;
    BasePizzaInterface* pizza3 = new OliveTop(new CheeseTop(new MargeritaBasePizza()));
    cout<<pizza3->cost()<<endl;
    BasePizzaInterface* pizza4 = new MushroomTop(new OliveTop(new CheeseTop(new MargeritaBasePizza())));
    cout<<pizza4->cost()<<endl;

    delete pizza1;
    delete pizza2;
    delete pizza3;
    delete pizza4;
    
    return 0;
}