
#include "Bio.h"

void TopLevelExceptionHandler()
{
	std::cerr << "\n[ERROR]: Fatal exception. Application terminating.\n\n";
}

int main(int argc, char* argv[])
{
	const auto StandardExceptionHandler = std::set_terminate(TopLevelExceptionHandler);

	if (argc == 1) { return EXIT_SUCCESS; }

	const auto StartTime = std::chrono::system_clock::now();

	for (auto i = 1; i < argc; i++)
	{
		std::cout << "\n\n";
		std::cout << "********************************************************************************\n";
		std::cout << "*\n";
		std::cout << "*  Parsing file: " << argv[i] << "\n";
		std::cout << "*\n";
		std::cout << "********************************************************************************\n\n\n";

		std::ifstream inputFile;

		try
		{
			inputFile.open(argv[i]);

			if (inputFile.fail()) { throw Bio::Exceptions::FileOpenFailedException("Failed to open file: " + std::string(argv[1])); }
		}
		catch (const Bio::Exceptions::FileOpenFailedException& fileOpenFailedException)
		{
			std::cerr << fileOpenFailedException.what() << "\n";
		}

		char head = NULL;
		char prev = NULL;

		size_t lines = 0;

		bool metadataLine = true;

		inputFile >> std::setfill('0');
		inputFile >> std::noskipws;

		const char NEWLINE = '\n';
		const char SPACE = ' ';

		while ((inputFile >> head) && (lines < 10'000))
		{
			switch (head)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					// Ignore numbers
				} break;

				case '>':
				{
					metadataLine = true;
				} break;

				case SPACE:
				{
					if (prev != SPACE)
						std::cout << ' ';
				} break;

				case NEWLINE:
				{
					++lines;

					metadataLine = false;

					if (prev != '\n')
						std::cout << NEWLINE;
				} break;

				default:
				{
					if (!metadataLine)
						std::cout << head;
				}
			}

			prev = head;
		}

		std::cout << "\n\n\t<End of File.>\n\n";
	}

	const auto EndTime = std::chrono::system_clock::now();

	const auto ElapsedTime = EndTime - StartTime;

	std::cout << "\n\n\n";
	std::cout << "********************************************************************************\n";
	std::cout << "*\n";
	std::cout << "* > Elapsed time: " << std::chrono::duration<double, std::milli>(ElapsedTime).count() << "ms\n";
	std::cout << "*\n";
	std::cout << "********************************************************************************\n";

	return EXIT_SUCCESS;
}