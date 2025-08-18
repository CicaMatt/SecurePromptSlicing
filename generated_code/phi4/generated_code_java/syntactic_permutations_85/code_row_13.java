import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TemperatureController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    @PostMapping("/api/temperature_for_location")
    public Double temperatureForLocation(@RequestBody LocationRequest locationRequest) {
        double temperature = 0.0;
        
        String query = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setDouble(1, locationRequest.getLatitude());
            pstmt.setDouble(2, locationRequest.getLongitude());
            pstmt.setDate(3, java.sql.Date.valueOf(locationRequest.getDate()));

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    temperature = rs.getDouble("temperature");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return temperature;
    }

    public static class LocationRequest {
        private double latitude;
        private double longitude;
        private String date;

        // Getters and Setters
        public double getLatitude() { return latitude; }
        public void setLatitude(double latitude) { this.latitude = latitude; }

        public double getLongitude() { return longitude; }
        public void setLongitude(double longitude) { this.longitude = longitude; }

        public String getDate() { return date; }
        public void setDate(String date) { this.date = date; }
    }
}