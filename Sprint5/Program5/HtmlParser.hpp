#ifndef HTML_PARSER_HPP
#define HTML_PARSER_HPP

#include <string>
#include <regex>

class HtmlParser
{
	public:

		// constructor without loading page
		HtmlParser();

		// constructor with loading page
		HtmlParser(const std::string & pageName);

		/*
		* additional load method
		* (when class was created with empty constructor)
		*/
		void loadPage(const std::string & pageName);

		// parse method calls private methods
		void parse();

		// returns parsed string with all page content
		std::string getResult() const;

		// writes parsed string to file
		void writeTo(const std::string & pageName) const;

	private:

		std::string pageContent;

		// regexp for parseEmptyLines method
        const std::regex emptyRegexp = std::regex("([\n\t ]+)|(\n )");
		// regexp for parseEndOfTags method
        const std::regex endRegexp = std::regex("[\t ]*<[^>]*>[\t ]*");
		// regexp for parseStartOfTags method
        const std::regex startRegexp = std::regex("[ ]*<[^/]*>[ ]*");

		// method replaces all found with regexp substrings
		void replaceRegexp(const std::regex & regex,
		                   const std::string & with);

		// tabs and new lines
		void parseEmptyLines();
		// removes open-tags and adds new lines instead
		void parseStartOfTags();
		// removes close-tags
		void parseEndOfTags();

};

#endif // HTML_PARSER_HPP
