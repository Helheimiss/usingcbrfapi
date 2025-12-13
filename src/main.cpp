#include "httplib.h"
#include <controller.h>


int main(int argc, char *argv[])
{
    httplib::Server svr;

    const static std::string CBRF_DATA = httplib::Client("http://www.cbr.ru")
        .Get("/scripts/XML_daily_eng.asp")->body;

    const static std::unique_ptr<std::string> CC_AND_NAMES = Parser::GetAllCharCodeAndName(CBRF_DATA);

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        const char *usage = R"(usage:
    /                               - help page                     # this page
    /CharCodes                      - print all CharCodes and Names
    /:Count/:CharCode               - example /100/USD              # Convert to RUB
    /:Count/:CharCode1/:CharCode2   - example /50/EUR/USD           # Converts 50 EUR to USD )";

        res.set_content(usage, "text/plain");
    });


    svr.Get("/CharCodes", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content(CC_AND_NAMES->c_str(), "text/plain");
    });


    svr.Get("/:Count/:CharCode1/:CharCode2", [](const httplib::Request& req, httplib::Response& res) {
        std::string CharCode1 = req.path_params.at("CharCode1");
        std::string CharCode2 = req.path_params.at("CharCode2");
        double Count = std::stod(req.path_params.at("Count"));

        std::string result = Convertor::ConvertValuteToValute(CBRF_DATA, Count, CharCode1, CharCode2);
        res.set_content(result, "text/plain");
    });


    svr.Get("/:Count/:CharCode", [](const httplib::Request& req, httplib::Response& res) {
        std::string CharCode = req.path_params.at("CharCode");
        double Count = std::stod(req.path_params.at("Count"));

        std::string result = Convertor::ConvertValute(CBRF_DATA, Count, CharCode);
        res.set_content(result, "text/plain");
    });


    svr.listen("0.0.0.0", 8080);
    return 0;
}