#include "httplib.h"
#include <controller.h>


int main(int argc, char *argv[])
{
    httplib::Server svr;

    const static std::string CBRF_DATA = httplib::Client("http://www.cbr.ru")
        .Get("/scripts/XML_daily_eng.asp")->body;

    static std::map<std::string, Valute> ValuteMap = Convertor::CreateMap(CBRF_DATA);

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        const char *usage = R"(usage:
    FFPU = <0/1>                            - Format Floating Point Unit    # (default FFPU=0) if 0 then FPU = , else FPU = .
    /                                       - help page                     # this page
    /CharCodes                              - print all CharCodes and Names # iso 4217
    /:Count/:CharCode?FFPU=0                - example /100/USD/1            # Convert to RUB
    /:Count/:CharCode1/:CharCode2?FFPU=0    - example /50/EUR/USD/          # Converts 50 EUR to USD )";

        res.set_content(usage, "text/plain");
    });


    svr.Get("/CharCodes", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("TODO()", "text/plain"); // TODO()
    });


    svr.Get("/:Count/:CharCode", [](const httplib::Request& req, httplib::Response& res) {
        std::string CharCode = req.path_params.at("CharCode");
        double Count = std::stod(req.path_params.at("Count"));
        std::string param;
        std::string FFPUResult;

        if (req.has_param("FFPU"))
            param = req.get_param_value("FFPU");

        if (param == "1") {
            FFPUResult = std::to_string(Convertor::ConvertValute(ValuteMap, Count, CharCode));
        }
        else {
            FFPUResult = std::to_string(Convertor::ConvertValute(ValuteMap, Count, CharCode));
        }


        res.set_content(FFPUResult, "text/plain");
    });


    svr.Get("/:Count/:CharCode1/:CharCode2", [](const httplib::Request& req, httplib::Response& res) {
        std::string CharCode1 = req.path_params.at("CharCode1");
        std::string CharCode2 = req.path_params.at("CharCode2");
        double Count = std::stod(req.path_params.at("Count"));
        std::string param;
        std::string FFPUResult;


        if (req.has_param("FFPU"))
            param = req.get_param_value("FFPU");

        if (param == "1") {
            FFPUResult = std::to_string(Convertor::ConvertValuteToValute(ValuteMap, Count, CharCode1, CharCode2));
        }
        else {
            FFPUResult = std::to_string(Convertor::ConvertValuteToValute(ValuteMap, Count, CharCode1, CharCode2));
        }


        res.set_content(FFPUResult, "text/plain");
    });


    svr.listen("0.0.0.0", 8080);
    return 0;
}