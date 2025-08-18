import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TemperatureController {

    @PostMapping("/api/temperature_for_location")
    public double temperature_for_location(@RequestBody LocationPayload payload) {
        double temperature = 0.0;
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String username = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String query = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setDouble(1, payload.getLatitude());
            statement.setDouble(2, payload.getLongitude());
            statement.setString(3, payload.getDate());

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                temperature = resultSet.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return temperature;
    }

    static class LocationPayload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public void setLatitude(double latitude) {
            this.latitude = latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public void setLongitude(double longitude) {
            this.longitude = longitude;
        }

        public String getDate() {
            return date;
        }

        public void setDate(String date) {
            this.date = date;
        }
    }
}