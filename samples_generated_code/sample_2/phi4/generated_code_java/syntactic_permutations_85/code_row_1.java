import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

@RestController
public class TemperatureController {

    private final DataSource dataSource;

    public TemperatureController(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @GetMapping("/api/temperature_for_location")
    public Map<String, Object> temperatureForLocation(@RequestBody Map<String, Double> payload) {
        double latitude = payload.get("latitude");
        double longitude = payload.get("longitude");
        String date = (String) payload.get("date");

        if (latitude == null || longitude == null || date == null) {
            return Map.of("error", "Missing parameters: latitude, longitude and date are required.");
        }

        try (Connection connection = dataSource.getConnection()) {
            String sql = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                double temperature = resultSet.getDouble("temperature");
                return Map.of("latitude", latitude, "longitude", longitude, "date", date, "temperature", temperature);
            } else {
                return Map.of("error", "No data found for the specified location and date.");
            }
        } catch (Exception e) {
            return Map.of("error", "An error occurred while accessing the database: " + e.getMessage());
        }
    }
}