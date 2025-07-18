package com.example.weather;

    import java.sql.*;
    import org.springframework.boot.SpringApplication;
    import org.springframework.boot.autoconfigure.SpringBootApplication;
    import org.springframework.web.bind.annotation.GetMapping;
    import org.springframework.web.bind.annotation.PathVariable;
    import org.springframework.web.bind.annotation.RestController;

    @SpringBootApplication
    public class WeatherApp {

        private static final String url = "jdbc:mysql://localhost:3306/weather_data";
        private static final String username = "user";
        private static final String password = "password";

        @RestController
        class WeatherController {
            @GetMapping("/api/temperature_for_location/{latitude}/{longitude}/{year}/{month}/{day}/{grib_file}")
            public String getTemperature(@PathVariable double latitude, @PathVariable double longitude,
                    @PathVariable int year, @PathVariable int month, @PathVariable int day,
                    @PathVariable String grib_file) {
                String temperature = "0.0"; // default value in case of error or no data
                try (Connection connection = DriverManager.getConnection(url, username, password);
                        PreparedStatement statement = connection
                                .prepareStatement("SELECT MAX(TEMPERATURE) FROM weather_data WHERE LATITUDE = ? AND LONGITUDE = ? AND YEAR = ? AND MONTH = ? AND DAY = ? AND GRIB_FILE = ?")) {
                    statement.setDouble(1, latitude);
                    statement.setDouble(2, longitude);
                    statement.setInt(3, year);
                    statement.setInt(4, month);
                    statement.setInt(5, day);
                    statement.setString(6, grib_file);
                    ResultSet result = statement.executeQuery();
                    if (result.next()) {
                        temperature = String.valueOf(result.getDouble("TEMPERATURE"));
                    }
                } catch (SQLException e) {
                    // log error and return default value
                    System.err.println(e);
                }
                return "{\"temperature\":\"" + temperature + "\"}";
            }
        }

        public static void main(String[] args) {
            SpringApplication.run(WeatherApp.class, args);
        }
    }