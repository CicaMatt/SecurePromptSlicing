import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@RestController
public class TemperatureController {

    private final DataSource dataSource;

    public TemperatureController(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @GetMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestParam double latitude, 
                                        @RequestParam double longitude,
                                        @RequestParam String date) {
        String temperature = getTemperatureFromDatabase(latitude, longitude, date);
        return "Temperature: " + (temperature != null ? temperature : "Not found");
    }

    private String getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection connection = dataSource.getConnection();
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return String.valueOf(resultSet.getDouble("temperature"));
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }
}