#include <iostream>
#include <vector>

using namespace std;

//int main() {
//  cout << "Hello World!";
//  return 0;
//}

int main() {
    vector<string> cars = {"Volvo", "Toyota", "Ford", "Mazda"};
    //for (int i = 0; i < cars.size(); i++) {
    //    cout << i << " " << cars[i] << "\n";
    for (string car : cars) {
        cout << car << "\n";
    }
    return 0;
}