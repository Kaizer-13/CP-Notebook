void print_solution(int a, int b, int c)
{
    int x, y;
    if (a == 0 && b == 0) {
        if (c == 0) {
            cout << "Infinite Solutions Exist" << endl;
        }
        else {
            cout << "No Solution exists" << endl;
        }
    }
    int gcd = gcd_extend(a, b, x, y);
    if (c % gcd != 0) {
        cout<< "No Solution exists"<< endl;
    }
    else {
        cout << "x = " << x * (c / gcd)<< ", y = " << y * (c / gcd)<< endl;
    }
}
