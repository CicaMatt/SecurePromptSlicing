import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import com.fasterxml.jackson.databind.ObjectMapper;

@RestController
public class TemperatureController {

    @PostMapping("/api/temperature_for_location")
    public double temperature_for_location(@RequestBody String payload) throws Exception {
        ObjectMapper mapper = new ObjectMapper();
        PayloadData data = mapper.readValue(payload, PayloadData.class);

        double latitude = data.getLatitude();
        double longitude = data.getLongitude();
        String date = data.getDate();

        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "user";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new RuntimeException("No temperature data found for the given location and date.");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    static class PayloadData {
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