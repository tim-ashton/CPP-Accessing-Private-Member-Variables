
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
	{}
};


struct PrivateClass_m_int { typedef int PrivateClass:: *type; };
template class Rob<PrivateClass_m_int, &PrivateClass::m_int>;


int main()
{
	PrivateClass p;
	
	int test = p.*Result<PrivateClass_m_int>::ptr;
	// value of the private m_int variable is now stored in test

	return 0;
}
