#include <bits/stdc++.h>
using namespace std;

class NotifObserverInterface
{
public:
    virtual void update() = 0;
    virtual ~NotifObserverInterface() {}
};

class StockObservableInterface
{
public:
    virtual void add(NotifObserverInterface* obs) = 0;
    virtual void remove(NotifObserverInterface* obs) = 0;
    virtual void notify() = 0;
    virtual void setData(int newData) = 0;
    virtual int getData() = 0;
    virtual ~StockObservableInterface() {}
};

class iPhoneObservable : public StockObservableInterface
{
public:
    vector<NotifObserverInterface*> observerList;
    int stockCount = 0;

    void add(NotifObserverInterface* obs)
    {
        observerList.push_back(obs);
    }

    void remove(NotifObserverInterface* obs)
    {
        auto it = find(observerList.begin(), observerList.end(), obs);
        if (it != observerList.end())
        {
            observerList.erase(it);
        }
    }

    void notify()
    {
        for (auto observer : observerList)
        {
            observer->update();
        }
    }

    void setData(int newData)
    {
        stockCount += newData;
        notify();
    }

    int getData()
    {
        return stockCount;
    }
};

class EmailObserver: public NotifObserverInterface
{
private:
    void sendMail(string email, string msg)
    {
        cout << msg << email << endl;
    }

public:
    string emailId;
    StockObservableInterface *observable;

    EmailObserver(string emailId, StockObservableInterface *observable)
    {
        this->emailId = emailId;
        this->observable = observable;
    }

    void update()
    {
        sendMail(emailId, "Hurry up ");
    }
};

int main()
{
    StockObservableInterface* iPhoneObservableObj = new iPhoneObservable;

    NotifObserverInterface* obs1 = new EmailObserver("xyz@gmail.com", iPhoneObservableObj);
    NotifObserverInterface* obs2 = new EmailObserver("yash@gmail.com", iPhoneObservableObj);

    iPhoneObservableObj->add(obs1);
    iPhoneObservableObj->add(obs2);

    iPhoneObservableObj->setData(10);
    iPhoneObservableObj->setData(20);

    delete obs1;
    delete obs2;
    delete iPhoneObservableObj;

    return 0;
}