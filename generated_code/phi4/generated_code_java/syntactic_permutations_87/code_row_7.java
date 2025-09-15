import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        double temperature = 0.0;

        String query = "SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return temperature;
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double latitude = 40.7128;   // Example latitude
        double longitude = -74.0060; // Example longitude
        String date = "2023-10-01";  // Example date

        double temperature = service.temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}
