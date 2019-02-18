
#pragma once

#include <exception>
#include <stdexcept>
#include <string>


namespace Bio
{
namespace Exceptions
{
/**
 * class FileException
 *
 * @brief
 * TODO: Add description
 *
 */
class FileException : public std::runtime_error
{
protected:
	std::string fileName;
	std::string errorMsg;

public:
	FileException(const std::string& fileName) : fileName { fileName }, std::runtime_error{ "" } { }

	virtual const char* what() const noexcept { return errorMsg.c_str(); }

	std::string getFileName() const noexcept { return fileName; }
};

} // namespace Exceptions
} // namespace Bio
