#include "HtmlParser.hpp"

#include <regex>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>

HtmlParser::HtmlParser()
{}

HtmlParser::HtmlParser(const std::string & pageName)
{
    loadPage(pageName);
}

void HtmlParser::loadPage(const std::string & pageName)
{
    std::stringstream input(pageName);

	if (!input)
	{
		throw std::invalid_argument("File was not opened");
	}

	input >> std::noskipws;

    std::copy(std::istream_iterator<char>(input),
              std::istream_iterator<char>(),
              std::back_inserter(pageContent));
}

void HtmlParser::replaceRegexp(const std::regex & regex, const std::string & with)
{
	std::string result = pageContent;

	std::sregex_iterator next(pageContent.begin(), pageContent.end(), regex);
	std::sregex_iterator end;

	while (next != end)
	{
		std::smatch match = *next;

		size_t found = result.find(match.str());

		if (found == std::string::npos)
		{
			continue;
		}

		result.replace(found, match.str().length(), with);
		next++;
	}

	pageContent = result;
}

void HtmlParser::parseEmptyLines()
{
	replaceRegexp(emptyRegexp, " ");
}

void HtmlParser::parseStartOfTags()
{
	replaceRegexp(startRegexp, "\n");
}

void HtmlParser::parseEndOfTags()
{
	replaceRegexp(endRegexp, "");
}

std::string HtmlParser::getResult() const
{
	return pageContent;
}

void HtmlParser::writeTo(const std::string & pageName) const
{
	std::fstream output(pageName);

	if (!output)
	{
		throw std::invalid_argument("File was not opened");
	}

	output << pageContent;
}

void HtmlParser::parse()
{
	parseEmptyLines();
	parseStartOfTags();
    parseEndOfTags();
}
