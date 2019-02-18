
#include "Bio.h"

enum class Nucleotides
{
	Guanine,
	Adenine,
	Thymine,
	Cytosine,
	Uracil
};

int main(int argc, char* argv[])
{
	if (argc == 1) { return EXIT_SUCCESS; }

	uint64_t GuanineCount = 0;
	uint64_t AdenineCount = 0;
	uint64_t ThymineCount = 0;
	uint64_t CytosineCount = 0;
	uint64_t UracilCount = 0;

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

				case 'A':
				case 'a':
				{
					++AdenineCount;
					std::cout << head;
				} break;

				case 'C':
				case 'c':
				{
					++CytosineCount;
					std::cout << head;
				} break;

				case 'G':
				case 'g':
				{
					++GuanineCount;
					std::cout << head;
				} break;

				case 'T':
				case 't':
				{
					++ThymineCount;
					std::cout << head;
				} break;

				case 'U':
				case 'u':
				{
					++UracilCount;
					std::cout << head;
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

	std::cout.imbue(std::locale("en_US"));

	std::cout << "\n\n\n";
	std::cout << "********************************************************************************\n";
	std::cout << "*\n";
	
	std::cout << "* Adenine Monomers:  ";
	auto& a = std::use_facet<std::num_put<char>>(std::cout.getloc());
	a.put(std::ostreambuf_iterator<char>(std::cout), std::cout, ' ', AdenineCount);
	std::cout << "\n";

	std::cout << "* Cytosine Monomers: ";
	auto& c = std::use_facet<std::num_put<char>>(std::cout.getloc());
	c.put(std::ostreambuf_iterator<char>(std::cout), std::cout, ' ', CytosineCount);
	std::cout << "\n";

	std::cout << "* Guanine Monomers:  ";
	auto& g = std::use_facet<std::num_put<char>>(std::cout.getloc());
	g.put(std::ostreambuf_iterator<char>(std::cout), std::cout, ' ', GuanineCount);
	std::cout << "\n";
	
	std::cout << "* Thymine Monomers:  ";
	auto& t = std::use_facet<std::num_put<char>>(std::cout.getloc());
	t.put(std::ostreambuf_iterator<char>(std::cout), std::cout, ' ', ThymineCount);
	std::cout << "\n";
	
	std::cout << "* Uracil Monomers:   ";
	auto& u = std::use_facet<std::num_put<char>>(std::cout.getloc());
	t.put(std::ostreambuf_iterator<char>(std::cout), std::cout, ' ', UracilCount);
	std::cout << "\n";
	
	std::cout << "*\n";
	std::cout << "*\n";
	std::cout << "* > Elapsed time: " << std::chrono::duration<double, std::milli>(ElapsedTime).count() << "ms\n";
	std::cout << "*\n";
	std::cout << "********************************************************************************\n";

	return EXIT_SUCCESS;
}