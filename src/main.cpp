#include "httplib.h"
#include <clocale>



int main(int argc, char *argv[])
{
    std::setlocale(LC_ALL, "");

    httplib::Server svr;
    httplib::Client cbrf("http://www.cbr.ru");

    auto cbrf_result = cbrf.Get("/scripts/XML_daily_eng.asp")->body;

    svr.Get("/:Count/:CharCode1/:CharCode2", [](const httplib::Request& req, httplib::Response& res) {
        std::string str1 = req.path_params.at("CharCode1");
        std::string str2 = req.path_params.at("CharCode2");
        double Count = std::stod(req.path_params.at("Count"));

        std::cout << Count << std::endl;
        std::cout << str1 << std::endl;
        std::cout << str2 << std::endl;


        res.set_content("", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}