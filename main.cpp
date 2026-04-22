#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


int main()
{
    ifstream file("output.csv");

    if(!file.is_open()){
        cerr << "ERROR OPENING FILE" << endl;
        return 1;
    }

    float cash = 10000.0;
    float portfolio = 0;
    int shares = 0;

    vector<pair<string,float>> equity_curve;

    string line, date, price, sign;

    int count = 0;

    while (getline(file, line)) {
        if (count >= 50) {
            stringstream s(line);
            getline(s, date, ',');
            getline(s, price, ',');
            getline(s, sign, ',');

            float fPrice = stof(price);
            
            if (sign == "BUY" && shares == 0){
                    shares = cash/fPrice;
                    cash = 0;
                    portfolio = cash + (shares * fPrice);
                    equity_curve.push_back({date,portfolio});

                }
            else if(sign == "SELL" && shares > 0){
                    cash = shares * fPrice;
                    shares = 0;
                    portfolio = cash + (shares * fPrice);
                    equity_curve.push_back({date,portfolio});
                }
            else{
                    portfolio = cash + (shares * fPrice);
                    equity_curve.push_back({date,portfolio});
            }
            }
            count++;
        }

        ofstream outfile("equity_curve.csv");
        outfile << "Date,Portfolio" << endl;

        for (auto& pair: equity_curve){
            outfile << pair.first << "," << pair.second << endl;
        }

        return 0;
    }


