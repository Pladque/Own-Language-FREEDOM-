#include <iostream>

#pragma once
class Error
{
	std::string error_name;
	std::string details;

public:
	Error(std::string error_name, std::string details);
	std::string as_string();
};

