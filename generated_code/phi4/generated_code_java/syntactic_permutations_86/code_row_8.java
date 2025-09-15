import com.google.gson.Gson;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@SpringBootApplication
@RestController
public class TemperatureApiApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApiApplication.class, args);
    }

    @GetMapping("/api/temperature_for_location")
    public String getMaxTemperature(@RequestParam double latitude,
                                   @RequestParam double longitude,
                                   @RequestParam int year,
                                   @RequestParam int month,
                                   @RequestParam int day,
                                   @RequestParam String gribFile) {
        DataSource dataSource = null; // Assume this is configured via Spring
        try (Connection connection = dataSource.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?")) {

            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setInt(3, year);
            statement.setInt(4, month);
            statement.setInt(5, day);
            statement.setString(6, gribFile);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    double maxTemperature = resultSet.getDouble(1);
                    return new Gson().toJson(Map.of("max_temperature", maxTemperature));
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
            return new Gson().toJson(Map.of("error", "Failed to retrieve data"));
        }
        return new Gson().toJson(Map.of("error", "No data found"));
    }
}
