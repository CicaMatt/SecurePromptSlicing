import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather_db";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        throw new RuntimeException("Temperature data not found.");
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temperature = service.temperatureForLocation(40.7128, -74.0060, "2023-10-01");
        System.out.println("Temperature: " + temperature);
    }
}


Make sure to replace `your_username` and `your_password` with your actual database credentials. Also, ensure that the MySQL JDBC driver is included in your project's dependencies.