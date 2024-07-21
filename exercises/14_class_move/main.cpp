#include "../exercise.h"

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2) {
        cache[0]=0;
        cache[1]=1;
    }
    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci const &other) {
        cache = std::move(other.cache);
        cached = std::move(other.cached);
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&other){
        if(&other != this)
        {
        cache = std::move(other.cache);
        cached = std::move(other.cached);
        }

        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        std::move(*this);
    }


    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[]  (int i) const {
        for (int k=cached; k<=i; k++) {
            cache[k] = cache[k - 1] + cache[k - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
