import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureFetcher {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername"; // replace with your database username
    private static final String PASS = "yourPassword"; // replace with your database password

    public double temperatureForLocation(double latitude, double longitude, java.sql.Date date) {
        String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND reading_date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setDate(3, date);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getDouble("temperature");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return Double.NaN; // Return NaN if no data is found
    }

    public static void main(String[] args) {
        TemperatureFetcher fetcher = new TemperatureFetcher();

        double latitude = 40.7128;
        double longitude = -74.0060;
        java.sql.Date date = java.sql.Date.valueOf("2023-10-01");

        double temperature = fetcher.temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}


**Note:** Make sure to replace `yourUsername` and `yourPassword` with your actual MySQL username and password. Ensure that the MySQL JDBC driver is included in your project's classpath.