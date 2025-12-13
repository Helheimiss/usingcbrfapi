#include "httplib.h"
#include <controller.h>


int main(int argc, char *argv[])
{
    httplib::Server svr;

    auto cbrf =
        httplib::Client("http://www.cbr.ru")
        .Get("/scripts/XML_daily_eng.asp")->body;


    svr.Get("/:Count/:CharCode1/:CharCode2", [cbrf](const httplib::Request& req, httplib::Response& res) {
        std::string CharCode1 = req.path_params.at("CharCode1");
        std::string CharCode2 = req.path_params.at("CharCode2");
        double Count = std::stod(req.path_params.at("Count"));

        std::string result = Convertor::ConvertValuteToValute(cbrf, Count, CharCode1, CharCode2);
        res.set_content(result, "text/plain");
    });

    svr.Get("/:Count/:CharCode", [cbrf](const httplib::Request& req, httplib::Response& res) {
        std::string CharCode = req.path_params.at("CharCode");
        double Count = std::stod(req.path_params.at("Count"));

        std::string result = Convertor::ConvertValute(cbrf, Count, CharCode);
        res.set_content(result, "text/plain");
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}