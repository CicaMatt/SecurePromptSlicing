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
    public double temperature_for_location(@RequestBody LocationPayload payload) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String username = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setDouble(1, payload.getLatitude());
            statement.setDouble(2, payload.getLongitude());
            statement.setDate(3, new java.sql.Date(payload.getDate().getTime()));

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -999.0; // Return a special value to indicate no data found or error
    }

    static class LocationPayload {
        private double latitude;
        private double longitude;
        private java.util.Date date;

        public double getLatitude() { return latitude; }
        public void setLatitude(double latitude) { this.latitude = latitude; }

        public double getLongitude() { return longitude; }
        public void setLongitude(double longitude) { this.longitude = longitude; }

        public java.util.Date getDate() { return date; }
        public void setDate(java.util.Date date) { this.date = date; }
    }
}