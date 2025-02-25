#include <bits/stdc++.h>
using namespace std;

class Internet {
public:
    virtual void connectTo(string website) = 0;
    virtual ~Internet() {}
};

//Implement the Real Object (RealInternet)
class RealInternet : public Internet {
public:
    void connectTo(string website) override {
        cout << "Connecting to " << website << "\n";
    }
};

//Implement the Proxy (ProxyInternet)
class ProxyInternet : public Internet {
private:
    RealInternet* realInternet;
    unordered_set<string> bannedSites;

public:
    ProxyInternet() {
        realInternet = new RealInternet();
        bannedSites = {"facebook.com", "youtube.com", "instagram.com"}; // Restricted sites
    }

    ~ProxyInternet() {
        delete realInternet;
    }

    void connectTo(string website) override {
        if (bannedSites.find(website) != bannedSites.end()) {
            cout << "Access Denied: " << website << " is blocked!\n";
        } else {
            realInternet->connectTo(website);
        }
    }
};

int main() {
    Internet* net = new ProxyInternet();

    net->connectTo("google.com");
    net->connectTo("facebook.com");
    net->connectTo("openai.com");
    net->connectTo("youtube.com");

    delete net;
    return 0;
}
