
#pragma once


#include "FileException.h"


namespace Bio
{
namespace Exceptions
{
/**
* class FileOpenFailedException
*
* @brief
* TODO: Add description
*
*/
class FileOpenFailedException : public FileException
{
public:
	FileOpenFailedException(const std::string& fileName) : FileException{ fileName }
	{
		errorMsg = "Failed to open file: " + fileName + "\n";
	}
};

} // namespace Exceptions
} // namespace Bio
