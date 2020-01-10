#include <iostream>
#include <string>

using namespace std;

template <typename T,int N>
class Array{
    int size{N};
    T values[N];

    friend ostream &operator<<(ostream &os, const Array<T,N> &arr){
        os << "[";
        for(auto &val:arr.values){
            os << val;
        }
        os << "]" << endl;
        return os;
    }

public:
    Array() = default;
    Array(T init_val){
        for(auto &item:values){
            item = init_val;
        }
    }

    void fill(T val){
        for(auto &item:values){
            item = val;
        }
    }

    int get_size() const {
        return size;
    }

    T &operator[](int index) {
        return values[index];
    }
};
int main()
{
    Array<int,5> nums;
    cout << "The size of nums is: "<< nums.get_size() << std::endl;
    cout << nums << endl;

    nums.fill(1);
    cout << nums << endl;

    nums.fill(10);
    cout << nums << "  "<< endl;

    nums[0] = 1000;
    nums[3] = 2000;
    cout << nums << "  " << endl;

    Array<string, 10> names(string("Abhay"));
    cout << "The size of strings is: "<< names.get_size() << endl;
    cout << names << endl;

    names[0] = string{"Larry"};
    cout << names << std::endl;

    names.fill(string{"X"});
    std::cout << names << std::endl;

    return 0;
}
