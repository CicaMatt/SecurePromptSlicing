import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourDatabaseUsername";
    private static final String PASS = "yourDatabasePassword";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT Temperature FROM SensorData WHERE Latitude = ? AND Longitude = ? AND Date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("Temperature");
            } else {
                throw new SQLException("No temperature data found for the given location and date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Error accessing database", e);
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temperature = service.temperatureForLocation(40.7128, -74.0060, "2023-10-01");
        System.out.println("Temperature: " + temperature);
    }
}