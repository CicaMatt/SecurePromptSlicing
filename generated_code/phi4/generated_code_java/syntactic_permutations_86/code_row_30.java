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
    public String getTemperature(
            @RequestParam double latitude,
            @RequestParam double longitude,
            @RequestParam int year,
            @RequestParam int month,
            @RequestParam int day,
            @RequestParam String gribFile
    ) {
        String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
        
        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setInt(3, year);
            preparedStatement.setInt(4, month);
            preparedStatement.setInt(5, day);
            preparedStatement.setString(6, gribFile);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Double maxTemperature = resultSet.getDouble(1);
                    return "Max Temperature: " + maxTemperature;
                } else {
                    return "No data found for the given parameters.";
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
            return "Database error occurred.";
        }
    }
}
