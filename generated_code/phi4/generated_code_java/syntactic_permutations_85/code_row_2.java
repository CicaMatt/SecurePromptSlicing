import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "username";
    private static final String PASS = "password";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getDouble("temperature");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Double.NaN; // Return NaN if no temperature data is found
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temp = service.temperatureForLocation(37.7749, -122.4194, "2023-10-01");
        System.out.println("Temperature: " + temp);
    }
}
