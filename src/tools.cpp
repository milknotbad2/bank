#include <iostream>
#include <limits>

auto maxLimit = numeric_limits<streamsize>::max();

#define VALIDATE_USER_INPUT(inputVariable, conditions, errorText); \
	while (!(cin >> inputVariable) conditions) \
	{ \
		cout << errorText << '\n'; \
		cin.clear(); \
		cin.ignore(maxLimit, '\n'); \
	}
	