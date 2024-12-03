//Add more headers and libaries for the code below
//General macro is a placeholder name
#include <iostream>
#include <string>
#include <vector>
#include <memory>



//Return type solver to convert string into double or int
class ReturnTypeSolver {
	const std::string& source;

public:
	explicit ReturnTypeSolver(const std::string& str) : source(str) {

	}

	operator int() {
		return std::stoi(source);
	}
	operator double() {
		return std::stod(source);
	}
};

//Remove example later
void Example() {
	std::string numbers = "123";
	int value1 = ReturnTypeSolver(numbers);
	double vakue2 = ReturnTypeSolver(numbers);
}

#ifndef VECTORREF 
	//FUCKING MACRO HAS FUCKED ME IN THE ASS WITH VECTOR
	//FIX THIS
	template <typename T, typename Vec = std::vector<T>>
	concept SameVectorType = requires(T t, Vec vec) {
		{ vec.push_back(t) };
	};
	template <typename T>
	using VectorRef = std::reference_wrapper<std::vector<T>>;
#endif
template <typename T> 
T FetchVectorItem(VectorRef<T> vector_type, T t) {
	
	return std::count
}


//This should probably be moved up or put into a different file with only macros
template <typename ...Args = std::vector_t> //Initilize to contains args in vector? 
#ifndef ALLOW_REMOVE_ITEMS
	template <typename T = std::nullptr_t, class C>
	concept DestructItem = std::is_class_v<C> && std::is_destructible_v<T>;
#elif 
	template <typename T> 
	concept DestructItem = std::
#else
	template <typenaem 
#endif

//Erase Remove
//Removes value from vector 
template <typename T>
void RemoveItem(std::vector<T>& v, const T& item, bool destroyitem) {
	v.erase(std::remove(v.begin(), v.end(), item), v.end());
	if (destroyitem) {

	}
}

void TryToErase() {
	std::vector<int> vector_example;
	Remove(vector_example, 99);
}

//RAII
//Helps manage deletion of resources for type saftey
template <typename T>
class ManageDeletion {
public:
	//Good to call explicit to force parameter use
	explicit ManageDeletion(T* type) : type_(type) {}
	~MangeDeletion() { delete _type }
private:
	T* type;
};