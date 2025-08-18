import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "user";
    private static final String PASS = "password";

    public double temperature_for_location(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -999.0; // Return a special value indicating no data found or error
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temperature = service.temperature_for_location(37.7749, -122.4194, "2023-10-01");
        System.out.println("Temperature: " + temperature);
    }
}