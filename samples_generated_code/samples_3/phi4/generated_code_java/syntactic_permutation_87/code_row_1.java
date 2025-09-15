import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.sql.DataSource;
import java.io.IOException;
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
    public String temperatureForLocation(
            @RequestParam double latitude,
            @RequestParam double longitude,
            @RequestParam String date) throws IOException {
        
        try (Connection connection = dataSource.getConnection();
             PreparedStatement statement = connection.prepareStatement("SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?")) {

            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return String.valueOf(resultSet.getDouble("temperature"));
                } else {
                    return "Temperature data not found";
                }
            }
        } catch (SQLException e) {
            throw new IOException("Database access error", e);
        }
    }
}
