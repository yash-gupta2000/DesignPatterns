#include <bits/stdc++.h>
using namespace std;

class ShapeInterface
{
public:
    virtual void draw() = 0;
    virtual ~ShapeInterface() {}
};

class SquareImpl : public ShapeInterface
{
public:
    void draw() override
    {
        cout << "Square shape construct"<<endl;
    }
};

class RectangleImpl : public ShapeInterface
{
public:
    void draw() override
    {
        cout << "Rectangle shape construct"<<endl;
    }
};

class CircleImpl : public ShapeInterface
{
public:
    void draw() override
    {
        cout << "Circle shape construct"<<endl;
    }
};

class ShapeFactory
{
public:
    ShapeInterface* getShape(string input)
    {
        if (input == "CIRCLE")
            return new CircleImpl();
        else if (input == "SQUARE")
            return new SquareImpl();
        else if (input == "RECTANGLE")
            return new RectangleImpl();
        else
            return nullptr;
    }
};

int main()
{
    ShapeFactory* shapeFactoryObj = new ShapeFactory();
    ShapeInterface* circleShape = shapeFactoryObj->getShape("CIRCLE");
    circleShape->draw();
    ShapeInterface* squareShape = shapeFactoryObj->getShape("SQUARE");
    squareShape->draw();
    ShapeInterface* rectangleShape = shapeFactoryObj->getShape("RECTANGLE");
    rectangleShape->draw();

    delete circleShape;
    delete squareShape;
    delete rectangleShape;
}