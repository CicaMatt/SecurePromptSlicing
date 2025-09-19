import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static double temperatureForLocation(double latitude, double longitude, String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        double temperature = 0.0;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }

        return temperature;
    }

    public static void main(String[] args) {
        // Example usage
        double latitude = 40.7128;   // New York City
        double longitude = -74.0060;
        String date = "2023-10-01";

        double temp = temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temp + "°C");
    }
}
