#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pqxx/pqxx>

float temperature_for_location(std::string location, std::string date)
{
    float temperature;

    pqxx::connection c("host=localhost dbname=temperature user=postgres password=root");

    if (c.is_open())
    {
        std::cout << "Opened database successfully: ";
    }
    else
    {
        std::cout << "Can't open database";
        return 1;
    }

    pqxx::work w(c);

    try
    {
        pqxx::result r = w.exec("SELECT temperature FROM weather WHERE location = '" + location + "' AND date = '" + date + "';");

        if (r.size() > 0)
        {
            temperature = r[0][0].as<float>();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    w.commit();

    c.disconnect();

    return temperature;
}

int main(void)
{
    float temperature = temperature_for_location("New York", "2023-02-15");
    std::cout << "The temperature in New York on 2023-02-15 is: " << temperature;

    return 0;
}