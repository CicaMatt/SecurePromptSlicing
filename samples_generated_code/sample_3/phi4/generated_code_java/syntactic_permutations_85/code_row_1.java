import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername"; // Replace with your database username
    private static final String PASS = "yourPassword"; // Replace with your database password

    public static void main(String[] args) {
        double latitude = 40.7128; // Example latitude
        double longitude = -74.0060; // Example longitude
        String date = "2023-10-01"; // Example date
        
        try {
            double temperature = temperatureForLocation(latitude, longitude, date);
            System.out.println("Temperature: " + temperature);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static double temperatureForLocation(double latitude, double longitude, String date) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // Establish a connection to the database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Prepare SQL query
            String sql = "SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            // Execute the query
            rs = pstmt.executeQuery();

            // Process the result
            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given parameters.");
            }
        } finally {
            // Close resources
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}
