import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.time.LocalDate;

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
    public Double temperatureForLocation(
            @RequestParam double latitude,
            @RequestParam double longitude,
            @RequestParam String date) throws Exception {
        
        try (Connection connection = dataSource.getConnection()) {
            String query = "SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setDate(3, java.sql.Date.valueOf(LocalDate.parse(date)));

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getDouble("temperature");
                    } else {
                        throw new Exception("No temperature data found for the specified location and date.");
                    }
                }
            }
        }
    }
}


This code requires a Spring Boot project setup with dependencies such as `spring-boot-starter-web` and `spring-boot-starter-jdbc`. Additionally, you need to configure your database connection in the `application.properties` file. Here's an example configuration:


spring.datasource.url=jdbc:mysql://localhost:3306/your_database
spring.datasource.username=your_username
spring.datasource.password=your_password

# For PostgreSQL:
# spring.datasource.url=jdbc:postgresql://localhost:5432/your_database
# spring.datasource.username=your_username
# spring.datasource.password=your_password


Replace `your_database`, `your_username`, and `your_password` with your actual database details.