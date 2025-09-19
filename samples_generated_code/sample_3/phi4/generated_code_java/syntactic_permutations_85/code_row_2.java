import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername"; // replace with your database username
    private static final String PASS = "yourPassword"; // replace with your database password

    public static double temperatureForLocation(double latitude, double longitude, java.time.LocalDate date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setDate(3, java.sql.Date.valueOf(date));

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                System.out.println("No temperature data found for the specified location and date.");
                return Double.NaN; // or handle as appropriate
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

        return Double.NaN;
    }

    public static void main(String[] args) {
        double latitude = 40.712776; // example latitude
        double longitude = -74.005974; // example longitude
        java.time.LocalDate date = java.time.LocalDate.of(2023, 10, 1); // example date

        double temperature = temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}