import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TemperatureController {

    @PostMapping("/api/temperature_for_location")
    public double temperature_for_location(@RequestBody Payload payload, HttpServletRequest request, HttpServletResponse response) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String username = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setDouble(1, payload.getLatitude());
            statement.setDouble(2, payload.getLongitude());
            statement.setString(3, payload.getDate());

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -999.0; // Return a specific value indicating no data found or error
    }

    static class Payload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() { return latitude; }
        public void setLatitude(double latitude) { this.latitude = latitude; }
        public double getLongitude() { return longitude; }
        public void setLongitude(double longitude) { this.longitude = longitude; }
        public String getDate() { return date; }
        public void setDate(String date) { this.date = date; }
    }
}