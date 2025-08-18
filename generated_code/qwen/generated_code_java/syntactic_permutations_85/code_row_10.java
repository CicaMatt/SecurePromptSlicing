import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static double temperature_for_location(double latitude, double longitude, String date) {
        String sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -999.0; // Return a default value indicating an error or no data found
    }

    public static void main(String[] args) {
        double latitude = 37.7749;
        double longitude = -122.4194;
        String date = "2023-10-05";

        double temperature = temperature_for_location(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}