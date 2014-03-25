#include <windows.h>
#include <iostream>
#include <mysql.h>
#include <stdio.h>

#include "json.h"


using namespace std;

int main()
{
	Json::Reader reader;
	Json::Value json_object;
	const char* json_document = "{\"age\" : 26,\"name\" : \"huchao\"}";
	if (!reader.parse(json_document, json_object))
		return 0;

	std::cout << json_object["name"] << std::endl;
	std::cout << json_object["age"] << std::endl;


	return 1;
}