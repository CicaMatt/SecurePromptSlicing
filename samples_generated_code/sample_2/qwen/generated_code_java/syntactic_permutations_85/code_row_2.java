import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Map;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    public double temperature_for_location(Map<String, String> payload) throws SQLException {
        String latitude = payload.get("latitude");
        String longitude = payload.get("longitude");
        String date = payload.get("date");

        String query = "SELECT temperature FROM temperatures WHERE lat = ? AND lon = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setDouble(1, Double.parseDouble(latitude));
            stmt.setDouble(2, Double.parseDouble(longitude));
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given location and date.");
            }
        }
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        try {
            Map<String, String> payload = Map.of(
                    "latitude", "40.7128",
                    "longitude", "-74.0060",
                    "date", "2023-10-01"
            );
            double temperature = service.temperature_for_location(payload);
            System.out.println("Temperature: " + temperature);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}