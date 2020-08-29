#include "ScrapingUtility.h"

#include <iterator>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

const std::regex CScrapingUtility::FILTER_PATTERN(R"(<tr style="text-align: center; background:#FFF">[\s\S]{1,600}</tr>)");
const int CScrapingUtility::NUM_FIELDS = 8;
const std::vector<std::regex> CScrapingUtility::FIELD_PATTERN=
{
	std::regex(R"(<b>)"),
	std::regex(R"(<td class="l">.+?>)"),
	std::regex(R"(<td style="background:#FF5959">)"),
	std::regex(R"(<td style="background:#F5AC78">)"),
	std::regex(R"(<td style="background:#FAE078">)"),
	std::regex(R"(<td style="background:#9DB7F5">)"),
	std::regex(R"(<td style="background:#A7DB8D">)"),
	std::regex(R"(<td style="background:#FA92B2">)"),
};

const std::vector<std::string> CScrapingUtility::FIELD=
{
	 "Number",
	"Name",
	"HP",
	"Attack",
	"Defence",
	"Sp. Attack",
	"Sp. Defence",
	"Speed",
};


std::vector<std::string> CScrapingUtility::FilterContents(void)
{
	std::vector<std::string> filterResult;

	std::sregex_iterator iter(m_sHtmlPage.cbegin(), m_sHtmlPage.cend(), FILTER_PATTERN);

	//sregex_iteratorのデフォルトコンストラクタは終端を表す
	std::sregex_iterator end;
	for (; iter != end; iter++)
	{
		filterResult.push_back(iter->str());
	}

	return filterResult;
}

Json CScrapingUtility::ParseItem(std::string sContent)
{
	Json parseResult;
	
	std::smatch match;
	auto iter = sContent.cbegin();
	auto end = sContent.cend();

	for (int i = 0; i < NUM_FIELDS; i++)
	{
		std::regex_search(iter, end, match, FIELD_PATTERN[i]);
		iter = match[0].second;
		std::string value = GetValue(sContent.substr(std::distance(sContent.cbegin(), iter)));
		parseResult[FIELD[i]] = value;
	}
	return parseResult;
}

std::string CScrapingUtility::GetValue(std::string sContent)
{
	return sContent.substr(0, sContent.find_first_of("<"));
}

void CScrapingUtility::scraping(void)
{
	std::vector<std::string> filterResult = FilterContents();

	std::vector<Json> jsonResult;
	for (auto& elem : filterResult)
	{
		jsonResult.push_back(ParseItem(elem));
	}

	std::ofstream outputFile("out.json");
	outputFile << jsonResult;
}