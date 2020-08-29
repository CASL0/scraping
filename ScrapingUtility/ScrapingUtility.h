#ifndef SCRAPINGUTILITY_H
#define SCRAPINGUTILITY_H

#include <string>
#include <vector>
#include <regex>
#include <nlohmann/json_fwd.hpp>

using Json = nlohmann::json;


class CScrapingUtility
{
public:
	CScrapingUtility(std::string sHtmlPage) :m_sHtmlPage(sHtmlPage){}
	~CScrapingUtility() = default;
	void scraping(void);

	static const std::regex FILTER_PATTERN;
	static const int NUM_FIELDS;
	static const std::vector<std::regex> FIELD_PATTERN;
	static const std::vector<std::string> FIELD;
private:
	std::vector<std::string> FilterContents(void);
	Json ParseItem(std::string sContent);
	std::string GetValue(std::string sContent);

	std::string m_sHtmlPage;
};

#endif