import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";  // Update with your username
    private static final String PASS = "";      // Update with your password

    public double temperatureForLocation(double latitude, double longitude, java.sql.Date date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND reading_date = ?";
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

        return Double.NaN;  // Return NaN if no temperature found
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();

        double latitude = 34.0522;
        double longitude = -118.2437;
        java.sql.Date date = java.sql.Date.valueOf("2023-10-01");

        double temperature = service.temperatureForLocation(latitude, longitude, date);
        
        System.out.println("Temperature: " + (temperature == Double.NaN ? "Not Available" : temperature));
    }
}


Make sure to replace `root` and the empty password string with your actual database username and password. You also need to ensure that the MySQL JDBC Driver is included in your project's classpath.