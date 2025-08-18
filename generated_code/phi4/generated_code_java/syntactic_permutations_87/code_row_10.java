import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        
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
        
        return Double.NaN; // Return NaN if no temperature data found
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double latitude = 40.7128;
        double longitude = -74.0060;
        String date = "2023-10-01";
        
        double temperature = service.temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}