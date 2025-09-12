import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "username"; // replace with your database username
    private static final String PASSWORD = "password"; // replace with your database password

    public static double temperatureForLocation(double latitude, double longitude, String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new RuntimeException("Temperature data not found for the given location and date.");
            }
        } catch (Exception e) {
            e.printStackTrace();
            return Double.NaN;
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        // Example usage
        double latitude = 40.7128;
        double longitude = -74.0060;
        String date = "2023-10-01";

        double temperature = temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}