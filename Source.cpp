#include <iostream>
#include <string>
#define N 5
int y;
using namespace std;

class tariff {          //êëàñ ÒÀĞÈÔÍÈÉ ÏÀÊÅÒ (çàäàşòüñÿ îïåğàòîğ òà íàçâà).
protected:
    string provider;
    string tar_name;
public:
    tariff() {
        provider = "";
        tar_name = "";
    }

    tariff(string str1, string str2) : provider(str1), tar_name(str2) {}
    ~tariff() {}
    string get_provider() { return provider; }
    string get_tar_name() { return tar_name; }
    virtual double total() { return 0; }
    bool operator<(tariff& p) {
        return this->total() < p.total();
    }
    bool operator>(tariff& p) {
        return this->total() > p.total();
    }
};

class tariff_plan : public tariff {        //ïîõ³äíèé êëàñ ÏÀÊÅÒ Ç ÀÁÎÍÏËÀÒÎŞ ÁÅÇ ÂÊËŞ×ÅÍÈÕ ÕÂÈËÈÍ
private:
    int subscriber_fee;
    int minute_price;
public:
    tariff_plan() : tariff(), subscriber_fee(0), minute_price(0) {}
    tariff_plan(string str1, string str2, int s_fee, int m_price) : tariff(str1, str2), subscriber_fee(s_fee), minute_price(m_price) {}
    ~tariff_plan() {}
    int get_subscriber_fee() { return subscriber_fee; }
    int get_minute_price() { return minute_price; }
    void set_fee_p(double p) { subscriber_fee = p; }
    void set_price_p(double p) { minute_price = p; }
    double total() { return (minute_price * y + subscriber_fee); }
};

class tariff_plan_nomin : public tariff {
private:
    int subscriber_fee;
    int num_minutes;
    int minute_price;
public:
    tariff_plan_nomin() : tariff(), subscriber_fee(0), minute_price(0), num_minutes(0) {}
    tariff_plan_nomin(string str1, string str2, int s_fee, int num_m, int m_price) : tariff(str1, str2), subscriber_fee(s_fee), num_minutes(num_m), minute_price(m_price) {}
    ~tariff_plan_nomin() {}
    int get_subscriber_fee() { return subscriber_fee; }
    int get_minute_price() { return minute_price; }
    int get_num_minutes() { return num_minutes; }
    void set_fee_p(double p) { subscriber_fee = p; }
    void set_price_p(double p) { minute_price = p; }
    double total() {
        if (num_minutes >= y)
            return (subscriber_fee);
        if (num_minutes < y)
            return (minute_price * (y - num_minutes) + subscriber_fee);
    }
};

ostream& operator<<(ostream& o, tariff p) {
    o << "Provider: " << p.get_provider() << "\t\tName of tariff: " << p.get_tar_name() << endl;
    return o;
}

ostream& operator<<(ostream& o, tariff_plan v) {
    o << "Provider: " << v.get_provider() << "\t\tName of tariff: " << v.get_tar_name() << "\n\t Subscriber's fee: " << v.get_subscriber_fee() << "\tPrice per minute: " << v.get_minute_price() << endl;
    return o;
}

void input(tariff** p) {
    int t;
    string s;
    string l;
    int s_fee, m_price, num_m;
    for (int i = 0; i < N; i++) {
        cout << "\n\tEnter type of tariff (1 - include minutes, 2 - doesn't include):\n";
        cin >> t;
        if (t == 1) {
            cout << "Provider: "; cin >> s;
            cout << "Name of tariff: "; cin >> l;
            cout << "Subscriber's fee: "; cin >> s_fee;
            cout << "Number of minutes: "; cin >> num_m;
            cout << "Price per minute: "; cin >> m_price;
            cout << "\n\n";

            p[i] = new tariff_plan_nomin(s, l, s_fee, num_m, m_price);

        }
        else if (t == 2) {
            cout << "Provider: "; cin >> s;
            cout << "Name of tariff: "; cin >> l;
            cout << "Subscriber's fee: "; cin >> s_fee;
            cout << "Price per minute: "; cin >> m_price;
            cout << "\n\n";

            p[i] = new tariff_plan(s, l, s_fee, m_price);
        }
    }
}

void sort(tariff** p, int x) {
    /*const int N = n;*/
    string package[N];
    double cost[N];    
    for (int i = 0; i < N; i++) {
        cost[i] = (*(p + i))->total();
        package[i] = (*(p + i))->get_tar_name();
    }
    cout << "\n\tTariffs for you:\n";
    for (int i = 0; i < N; i++) {
        if (cost[i] < x)
            cout << package[i] << " - " << cost[i] << " grivnas" << endl;
    }
}

int main() {
    tariff* (*p);
    int x;
    //const int n=5;
    ///*cout << "Enter number of tariff's: ";
    //cin >> n;*/
    p = new tariff * [N];
    input(p);
    cout << "Enter amount of money you can pay: ";
    cin >> x;
    cout << "Enter number of minutes you want to use: ";
    cin >> y;
    sort(p,x);
    return 0;
}