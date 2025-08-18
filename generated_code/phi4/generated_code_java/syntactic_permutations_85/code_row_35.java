import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Map;

@SpringBootApplication
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }
}

@RestController
class TemperatureController {

    private final DataSource dataSource;

    public TemperatureController(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @PostMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestBody Map<String, String> payload) {
        String latitude = payload.get("latitude");
        String longitude = payload.get("longitude");
        String date = payload.get("date");

        if (latitude == null || longitude == null || date == null) {
            return "Invalid input";
        }

        try (Connection connection = dataSource.getConnection()) {
            String sql = "SELECT temperature FROM sensor WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, latitude);
                statement.setString(2, longitude);
                statement.setString(3, date);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double temperature = resultSet.getDouble("temperature");
                        return "Temperature: " + temperature;
                    } else {
                        return "No data found";
                    }
                }
            }
        } catch (Exception e) {
            return "Error retrieving data: " + e.getMessage();
        }
    }
}


To make this code runnable, you need to set up a Spring Boot application with the necessary dependencies in your `pom.xml` or `build.gradle`, and configure a database connection. Here's an example of how you might define the `DataSource` bean:


import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.jdbc.datasource.DriverManagerDataSource;

import javax.sql.DataSource;

@Configuration
class DataSourceConfig {

    @Bean
    public DataSource dataSource() {
        DriverManagerDataSource dataSource = new DriverManagerDataSource();
        dataSource.setDriverClassName("com.mysql.cj.jdbc.Driver");
        dataSource.setUrl("jdbc:mysql://localhost:3306/your_database");
        dataSource.setUsername("your_username");
        dataSource.setPassword("your_password");
        return dataSource;
    }
}
 

Replace `"your_database"`, `"your_username"`, and `"your_password"` with your actual database details.