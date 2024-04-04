/***
    double pi = 3.14;
    cout << setprecision(5) << fixed << pi << endl;
    --> 3.14000

    cout << setw(5) << 20;
    --> "   20"

    cout << setiosflags(ios::left) << setw(5) << 20 << endl;
    --> "20   "

    cout << setiosflags(ios::right) << setw(5) << 20 << endl;
    --> "   20"

    cout << setfill('0'); fills the blanks created by setw(w) function


    Printing Date :

    void showDate(int m, int d, int y) {
        cout << setfill('0');
        cout << setw(2) << m << '/' << setw(2) << d << '/' << setw(4) << y << endl;
    }


    Base Conversion :
    int x = 2324534;
    cout << dec << x << endl;
    cout << oct << x << endl;
    cout << hex << x << endl;
***/
