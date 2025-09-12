import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static double temperatureForLocation(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM temperatures WHERE lat = ? AND lon = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new IllegalArgumentException("Temperature not found for the given location and date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Database error occurred", e);
        }
    }

    public static void main(String[] args) {
        // Example usage
        double temperature = temperatureForLocation(37.7749, -122.4194, "2023-10-01");
        System.out.println("Temperature: " + temperature);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.