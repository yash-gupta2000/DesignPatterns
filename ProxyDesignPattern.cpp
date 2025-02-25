#include <bits/stdc++.h>
using namespace std;

class EmployeeDao
{
public:
    EmployeeDao() {}
    virtual void create(string type, int employeeId) = 0;
    virtual void remove(string type, int employeeId) = 0;
    virtual EmployeeDao *fetch(string type, int employeeId) = 0;
};

class EmployeeDaoImpl : public EmployeeDao
{
public:
    void create(string type, int employeeId) override
    {
        cout << "Employee record has been created" << "\n";
    }

    void remove(string type, int employeeId) override
    {
        cout << "Employee record has been deleted" << "\n";
    }

    EmployeeDao *fetch(string type, int employeeId) override
    {
        cout << "Fetched employee record for " << employeeId << "\n";
        return new EmployeeDaoImpl();
    }
};

class EmployeeDaoProxy : public EmployeeDao
{
public:
    EmployeeDaoImpl *employeeDaoObj;
    EmployeeDaoProxy()
    {
        employeeDaoObj = new EmployeeDaoImpl();
    }

    void create(string type, int employeeId) override
    {
        if (type == "CLIENT")
        {
            employeeDaoObj->create("",0);
            return;
        }
        throw runtime_error("ACCESS DENIED");
    }

    void remove(string type, int employeeId) override
    {
        if (type == "CLIENT")
        {
            employeeDaoObj->remove("", 0);
            return;
        }
        throw runtime_error("ACCESS DENIED");
    }

    EmployeeDao *fetch(string type, int employeeId) override
    {
        if (type == "ADMIN" || type == "USER")
        {
            return employeeDaoObj->fetch(type, employeeId);
        }
        throw runtime_error("ACCESS DENIED");
    }
};

int main()
{
    try
    {
        EmployeeDao *empObj = new EmployeeDaoProxy();
        empObj->create("CLIENT", 12345);
        cout << "Successfull";
    }
    catch (exception &e)
    {
        cout << e.what();
    }
}
