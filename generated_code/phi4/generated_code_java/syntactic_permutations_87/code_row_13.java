import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WeatherService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather_db";
    private static final String USER = "your_database_username";
    private static final String PASS = "your_database_password";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given location and date.");
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

        return Double.NaN; // Return NaN if no data found or an error occurs
    }

    public static void main(String[] args) {
        WeatherService service = new WeatherService();
        double latitude = 40.7128;
        double longitude = -74.0060;
        String date = "2023-10-15";

        double temperature = service.temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}