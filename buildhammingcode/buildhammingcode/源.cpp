#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

int getW(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int cal(int k)
{
    int num = 0;
    while (k > (pow(3, num) - 1) / 2)
    {
        k++;
        num++;
    }
    return num;
}
bool encode(const string& s, string& d)
{
    d.clear();
    auto k = cal(s.size());
    d.resize(s.size() + k);
    std::vector<int> mac;
    int size = d.size();
    for (int i = 0, j = 0, p = 0; i != size; i++)
    {
        if (i == (pow(3, p) - 1) / 2 && p < k)
        {
            mac.push_back(0);
            p++;
        }
        else if (s[j] == '0')
        {
            mac.push_back(0);
            j++;
        }
        else if (s[j] == '1')
        {
            mac.push_back(1);
            j++;
        }
        else if (s[j] == 'T')
        {
            mac.push_back(-1);
            j++;
        }
        else
            return false;
    }
    int sum = 0, num = 1, numc = 0, clock = 0;
    for (int i = k; i >= 1; i--)
    {
        cout << "i : " << i << endl;
        clock = pow(3, i - 1);
        sum = 0;
        num = 1;
        cout << "clock : " << clock << endl;
        for (int n = (pow(3, i - 1) - 1) / 2 + 2; n <= size; n++)
        {
            clock--;
            if (clock == 0)
            {
                if (num == 1) { num = -1; }
                else if (num == -1) { num = 0; }
                else { num = 1; }
                clock = pow(3, i - 1);
            }
            if (mac[n - 1] != 0 && num != 0) {
                numc = num * mac[n - 1];
                if (numc == 1) { sum = (sum == 1) ? -1 : ((sum == -1) ? 0 : 1); }
                else if (numc == -1) { sum = (sum == 1) ? 0 : ((sum == 0) ? -1 : 1); }
                cout << "n :  " << n << "   mac[" << n - 1 << "] : " << mac[n - 1] << "   num : " << num << "   sum : " << sum << endl;
            }
        }
        if (sum == 1) sum = -1;
        else if (sum == -1)sum = 1;
        mac[(pow(3, i - 1) - 1) / 2] = sum;
        cout << "(pow(3, i - 1) - 1) / 2 + 1 :" << (pow(3, i - 1) - 1) / 2 + 1 << "   "; //true
        cout << "mac[" << i << "] :" << sum << endl;
    }
    for (int i = 0; i < size; i++)
    {
        if (mac[i] == 0)  d[i] = '0';
        else if (mac[i] == 1) d[i] = '1';
        else if (mac[i] == -1) d[i] = 'T';
        else return false;
        cout << "mac[" << i << "] :" << mac[i] << "   ";
        cout << "d[" << i << "] :" << d[i] << endl;
    }
    return true;
}

int antical(int k)
{
    int num = 0;
    while (k > (pow(3, num) - 1) / 2)
    {
        num++;
    }
    return num;
}

int decode(string& s, string& d)
{
    s.clear();
    int k = antical(d.size());
    s.resize(d.size() - k);
    std::vector<int> mac;
    std::vector<int> errcw;
    int size = s.size();
    for (int j = 0; j < d.size(); j++)
    {
        if (d[j] == '0') mac.push_back(0);
        else if (d[j] == '1') mac.push_back(1);
        else if (d[j] == 'T') mac.push_back(-1);
        else return false;
    }
    int sum = 0, num = 1, numc = 0, clock = 0, isright = 1;
    for (int i = k; i >= 1; i--)
    {
        cout << "i : " << i << endl;
        clock = pow(3, i - 1);
        sum = 0;
        num = 1;
        cout << "clock : " << clock << endl;
        for (int n = (pow(3, i - 1) - 1) / 2 + 1; n <= d.size(); n++)
        {
            numc = num * mac[n - 1];
            if (numc == 1) { sum = (sum == 1) ? -1 : ((sum == -1) ? 0 : 1); }
            else if (numc == -1) { sum = (sum == 1) ? 0 : ((sum == 0) ? -1 : 1); }
            cout << "n :  " << n << "   mac[" << n - 1 << "] : " << mac[n - 1] << "   num : " << num << "   sum : " << sum << endl;
            clock--;
            if (clock == 0)
            {
                if (num == 1) { num = -1; }
                else if (num == -1) { num = 0; }
                else { num = 1; }
                clock = pow(3, i - 1);
            }
        }
        if (sum != 0) isright = 0;
        errcw.push_back(sum);
        cout << "sum : " << sum << endl;
    }
    sum = 0;
    if (isright == 1) return 0;
    else {
        for (int i = 0; i <= k - 1; i++)
        {
            sum = sum + errcw[i] * pow(3, i);
        }
        if (sum > 0)
        {
            mac[sum - 1] = (mac[sum - 1] == 1) ? 0 : ((mac[sum - 1] == 0) ? -1 : 1);
        }
        else
        {
            sum = -1 * sum;
            mac[sum - 1] = (mac[sum - 1] == 1) ? -1 : ((mac[sum - 1] == -1) ? 0 : 1);
        }
    }
    cout << "Last place error : " << sum << endl;
    if (mac[sum - 1] == 0)  d[sum - 1] = '0';
    else if (mac[sum - 1] == 1) d[sum - 1] = '1';
    else if (mac[sum - 1] == -1) d[sum - 1] = 'T';
    cout << "mac[" << sum - 1 << "] :" << mac[sum - 1] << "   ";
    cout << "d[" << sum - 1 << "] :" << d[sum - 1] << endl;
    for (int i = 0, j = 0, p = 0; i != size; i++)
    {
        if (i == (pow(3, p) - 1) / 2 && p < k)
        {
            p++;
            j++;
        }
        else
        {
            s[i] = d[j];
            j++;
            cout << "i : " << i << "   s[i] :" << s[i] << endl;
        }
    }
    return sum;
}

int main()
{
    string source, dest;
    char service;
    cout << "Please choose a service : 1: Formation 2 : Splitting" << endl;
    cin >> service;
    if (service != '1' && service != '2')
    {
        cout << "service error!" << endl;
    }
    if (service == '1')
    {
        while (cin >> source)
        {
            if (encode(source, dest))
            {
                cout << "Source: " << source << endl;
                cout << "Dest: " << dest << endl;
            }
        }
    }

    else if (service == '2')
    {
        while (cin >> dest)
        {
            int ret = decode(source, dest);
            cout << "Code " << dest << endl;
            cout << "RET " << ret << endl;
            if (ret == 0)
            {
                cout << "Source: " << source << endl;
                cout << "Dest: " << dest << endl;
            }
            else
            {
                cout << "Error index " << ret << endl;
                cout << "Corret source: " << source << endl;
                cout << "Corret dest: " << dest << endl;
            }
            cout << endl;
        }
    }

    return 0;
}