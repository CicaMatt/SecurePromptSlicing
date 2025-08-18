import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    public double temperature_for_location(String payload) {
        String[] data = payload.split(",");
        double latitude = Double.parseDouble(data[0]);
        double longitude = Double.parseDouble(data[1]);
        String date = data[2];

        String query = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
        
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

        return Double.NaN; // Return NaN if no temperature is found
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        String payload = "37.7749,-122.4194,2023-10-01";
        double temperature = service.temperature_for_location(payload);
        System.out.println("Temperature: " + temperature);
    }
}