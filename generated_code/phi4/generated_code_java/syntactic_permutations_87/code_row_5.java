import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

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

    @GetMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestParam double latitude, 
                                        @RequestParam double longitude,
                                        @RequestParam String date) {
        try (Connection connection = dataSource.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?")) {

            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return Double.toString(resultSet.getDouble("temperature"));
                } else {
                    return "No temperature data found for the provided location and date.";
                }
            }

        } catch (SQLException e) {
            return "Error accessing database: " + e.getMessage();
        }
    }
}


To run this code, make sure you have a Spring Boot setup with dependencies on `spring-boot-starter-web` and `spring-boot-starter-jdbc`. Additionally, configure the data source to connect to your database. You might need a table named `temperatures` with columns `latitude`, `longitude`, `date`, and `temperature` in your database.