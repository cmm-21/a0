#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    std::ifstream file(CMM_MY_INFO);
    auto json = nlohmann::json::parse(file);
    file.close();

    std::cout << "full name : " << json["full name"] << std::endl;
    std::cout << "student id: " << json["student id"] << std::endl;
    std::cout << "nethz name: " << json["nethz name"] << std::endl;

    return 0;
}
