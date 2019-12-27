#include "DictionaryStringInt.h"

int main()
{

		Dictionary* d = new Dictionary();
		d->put("d", 44);
		d->put("dd", 135);
		d->put("ddd", 123);

		std::cout << d->get("dd");
		
}