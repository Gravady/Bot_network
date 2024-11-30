#include <iostream>
#include <string>

//Pratice CRTP with something like this

template <class Derived> 
class Animals {
public:
	template<typename Func, typename ...Args>
	void CallFunction(Func&& func, Args&&... args) {
		(static_cast<Derived*>(this)->*func)(std::forward<Args>(args)...); //Forwarding
	}
};

class Dog : public Animals<Dog> {
public:
	void GetAnimal() {
		std::cout << "Got an animal";
	}
	void Bark() {
		std::cout << "Woof woof";
	}
};

int main() {
	Dog dog;
	dog.CallFunction(&Dog::GetAnimal);
	return 0;
}


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

void Example() {
	std::string numbers = "123";
	int value = ReturnTypeSolver(numbers);
	double value = ReturnTypeSolver(numbers);
}

//Erase Remove
//Removes value from vector 
template <typename T>
inline void Remove(std::vector<T>& v, const T& item) {
	v.erase(std::remove(v.begin(), v.end(), item), v.end());
}

void TryToErase() {
	std::vector<int> vector_example;
	Remove(vector_example, 99);
}

//RAII
//Helps manage deletion of resources for type saftey
template <typename T>
class ManageDeletion() {
public:
	//Good to call explicit to force parameter use
	explicit ManageDeletion(T *type) : type_(type){}
	~MangeDeletion() {delete _type}
private:
	T* type;
}