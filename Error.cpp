#include "Error.h"

Error::Error(std::string error_name, std::string details)
{
	this->error_name = error_name;
	this->details = details;

}

std::string Error::as_string()
{
	return this->error_name + ": " + this->details;
}