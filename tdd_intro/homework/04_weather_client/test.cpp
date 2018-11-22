/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data from weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day and time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement fake server, because interacting with real network is inacceptable within the unit tests.
To do this, you need to use real server responses. Fortunately, you've collected some results for the several dates from the weather server.
Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

IMPORTANT:
* Server returns empty string if request is invalid.
* Real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date. Do not use other hours in a day.

2. Implement IWeatherClient using fake server.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

template<typename T>
size_t parse_number(const std::string& str, size_t pos, T &out)
{
    auto next_pos = str.find(";", pos);
    std::string tmp = str.substr(pos, next_pos);
    out = std::stod(tmp);

    return next_pos;
}

struct Weather
{
    short temperature = 0;
    unsigned short windDirection = 0;
    double windSpeed = 0;

    Weather(const std::string& str)
    {
        auto temp_pos = parse_number(str, 0, temperature);
        auto dir_pos = parse_number(str, temp_pos + 1, windDirection);
        parse_number(str, dir_pos + 1, windSpeed);
    }

    bool operator==(const Weather& right)
    {
        return temperature == right.temperature &&
               windDirection == right.windDirection &&
               std::abs(windSpeed - right.windSpeed) < 0.01;
    }
};

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

class MockWeatherServer: public IWeatherServer
{
public:
    MOCK_METHOD1(GetWeather, std::string(const std::string& request));
};

// Implement this interface
class IWeatherClient
{
public:
    virtual ~IWeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) = 0;
};

static const size_t WEATHER_RECORDS_PER_DAY = 4;
static const std::string WEATHER_TIMES[WEATHER_RECORDS_PER_DAY] = {
    "03:00", "09:00", "15:00", "21:00"
};

Weather get_weather(IWeatherServer& server, const std::string &date, const std::string &time)
{
    return Weather(server.GetWeather(date + ";" + time));
}

class WeatherClient: public IWeatherClient
{
public:
    double GetAverageTemperature(IWeatherServer& server, const std::string& date) override
    {
        double sum = 0.0;
        for (auto &time: WEATHER_TIMES) {
            sum += get_weather(server, date, time).temperature;
        }
        return sum / 4.0;
    }

    double GetMinimumTemperature(IWeatherServer& server, const std::string& date) override
    {
        double min = get_weather(server, date, WEATHER_TIMES[0]).temperature;
        for (size_t i = 1; i < WEATHER_RECORDS_PER_DAY; ++i) {
            double temp = get_weather(server, date, WEATHER_TIMES[i]).temperature;
            min = std::min(temp, min);
        }
        return min;
    }

    double GetMaximumTemperature(IWeatherServer& server, const std::string& date) override
    {
    }

    double GetAverageWindDirection(IWeatherServer& server, const std::string& date) override
    {
    }

    double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) override
    {
    }
};

using ::testing::Return;
using ::testing::_;

TEST(WeatherClientTest, average_temp_for_same_return_it) {
    MockWeatherServer server;
    WeatherClient client;

    EXPECT_CALL(server, GetWeather(_))
        .WillRepeatedly(Return("20;181;5.1"));

    ASSERT_EQ(client.GetAverageTemperature(server, "31.08.2018"), 20);
}

TEST(WeatherClientTest, average_temp_for_2_different_return_their_average) {
    static const std::string RESULTS[WEATHER_RECORDS_PER_DAY] = {
        "20;181;5.1", "10;181;5.1", "20;181;5.1", "10;181;5.1"
    };

    MockWeatherServer server;
    WeatherClient client;

    for (size_t i = 0; i < WEATHER_RECORDS_PER_DAY; ++i) {
        EXPECT_CALL(server, GetWeather("31.08.2018;" + WEATHER_TIMES[i]))
            .WillRepeatedly(Return(RESULTS[i]));
    }

    ASSERT_EQ(client.GetAverageTemperature(server, "31.08.2018"), 15);
}

TEST(WeatherClientTest, average_temp_for_4_different_return_their_average) {
    static const std::string RESULTS[WEATHER_RECORDS_PER_DAY] = {
        "10;181;5.1", "15;181;5.1", "20;181;5.1", "25;181;5.1"
    };

    MockWeatherServer server;
    WeatherClient client;

    for (size_t i = 0; i < WEATHER_RECORDS_PER_DAY; ++i) {
        EXPECT_CALL(server, GetWeather("31.08.2018;" + WEATHER_TIMES[i]))
            .WillRepeatedly(Return(RESULTS[i]));
    }

    ASSERT_EQ(client.GetAverageTemperature(server, "31.08.2018"), 17.5);
}

TEST(WeatherClientTest, min_temp_for_4_different_return_their_average) {
    static const std::string RESULTS[WEATHER_RECORDS_PER_DAY] = {
        "10;181;5.1", "15;181;5.1", "20;181;5.1", "25;181;5.1"
    };

    MockWeatherServer server;
    WeatherClient client;

    for (size_t i = 0; i < WEATHER_RECORDS_PER_DAY; ++i) {
        EXPECT_CALL(server, GetWeather("31.08.2018;" + WEATHER_TIMES[i]))
            .WillRepeatedly(Return(RESULTS[i]));
    }

    ASSERT_EQ(client.GetMinimumTemperature(server, "31.08.2018"), 10.0);
}

TEST(WeatherTest, temperature_is_parsed_correctly) {
    ASSERT_EQ(Weather("20;181;5.1").temperature, 20);
}

TEST(WeatherTest, wind_direction_is_parsed_correctly) {
    ASSERT_EQ(Weather("20;181;5.1").windDirection, 181);
}

TEST(WeatherTest, wind_speed_is_parsed_correctly) {
    ASSERT_EQ(Weather("20;181;5.1").windSpeed, 5.1);
}
