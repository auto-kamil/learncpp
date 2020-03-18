#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <memory>

using namespace std;

constexpr long iter_cnt = 2000;
using used_resolution = std::chrono::microseconds;

// static linking type interface
template <typename Impl>
class ICrtpCallback
{
public:
    // interface
    void callback()
    {
        static_cast<Impl *>(this)->callback_implementation();
    }

protected:
    // disable deletion of Derived* through Base*
    // enable deletion of Base* through Derived*
    ~ICrtpCallback() = default;
};

class CrtpImpl
    : public ICrtpCallback<CrtpImpl>
{
private:
    // implementation
    friend class ICrtpCallback<CrtpImpl>;
    void callback_implementation()
    {
        test++;
    }
    volatile int test = 0;
};

// dynamic linking type interface
class ICallback
{
public:
    virtual ~ICallback() {}
    virtual void callback() = 0;
};

class CallbackImplStandard : public ICallback
{
public:
    void callback()
    {
        test++;
    }

private:
    volatile int test = 0;
};

class CallbackImplFinal : public ICallback
{
public:
    virtual void callback() final override
    {
        test++;
    }

private:
    volatile int test = 0;
};

CrtpImpl impl_crtp;
CallbackImplStandard impl_std;
CallbackImplFinal impl_perfect;

//----------------------------------------------------------------------------------
// Tests 
//----------------------------------------------------------------------------------


auto CtrpTest(ICrtpCallback<CrtpImpl>& crt_test_obj)
{
    auto before = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < iter_cnt; i++)
    {
        crt_test_obj.callback();
    }
    auto after = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<used_resolution>(after - before).count();
}

auto DynamicImplTest(ICallback& test_obj)
{
    auto before = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < iter_cnt; i++)
    {
        test_obj.callback();
    }
    auto after = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<used_resolution>(after - before).count();
}

int main()
{
    cout << "Dynamic polimorphism, exect time:                 " << DynamicImplTest(impl_std) << endl;
    cout << "Dynamic polimorphism (final keyword), exect time: " << DynamicImplTest(impl_perfect) << endl;
    cout << "CRTP test, exect time:                            " << CtrpTest(impl_crtp) << endl;

    return 0;
}