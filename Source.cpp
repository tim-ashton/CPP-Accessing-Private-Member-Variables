#include <iostream>

template<typename Tag>
struct Result {
	/* export it ... */
	typedef typename Tag::type type;
	static type ptr;
};

template<typename Tag>
typename Result<Tag>::type Result<Tag>::ptr;

template<typename Tag, typename Tag::type p>
struct Rob : Result<Tag> {
	/* fill it ... */
	struct Filler {
		Filler() { Result<Tag>::ptr = p; }
	};
	static Filler filler_obj;
};

template<typename Tag, typename Tag::type p>
typename Rob<Tag, p>::Filler Rob<Tag, p>::filler_obj;


class PrivateClass
{
    int m_int;

  public:
    PrivateClass()
        : m_int(100)
    {
    }

  private:
    bool IsEven(unsigned int test_val)
    {
        return (test_val % 2) == 0;
    }
};

// Access the private integer value of PrivateClass
struct PrivateClass_m_int
{
    typedef int PrivateClass::*type;
};
template class Rob<PrivateClass_m_int, &PrivateClass::m_int>;

// Access the private function of PrivateClass
struct PrivateClass_IsEven
{
    typedef bool (PrivateClass::*type)(unsigned int);
};
template class Rob<PrivateClass_IsEven, &PrivateClass::IsEven>;

int main()
{
    PrivateClass p;

    int test = p.*Result<PrivateClass_m_int>::ptr;
    std::cout << "The value of private int is : " << test << std::endl;

    // Call private IsEven function
    if ((p.*Result<PrivateClass_IsEven>::ptr)(2))
    {
        std::cout << "Its Even!" << std::endl;
    }
    else
    {
        std::cout << "Its Odd!" << std::endl;
    }

    return 0;
}
