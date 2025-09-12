import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername"; // replace with your username
    private static final String PASS = "yourPassword"; // replace with your password

    public double temperatureForLocation(double latitude, double longitude, java.sql.Date date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setDate(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }

        return Double.NaN; // Return NaN if temperature not found
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        java.sql.Date date = java.sql.Date.valueOf("2023-10-01");
        double temperature = service.temperatureForLocation(37.7749, -122.4194, date);
        System.out.println("Temperature: " + temperature);
    }
}


Note: Make sure to replace `yourUsername` and `yourPassword` with your actual database credentials. Also, ensure that the MySQL JDBC driver is in your classpath.