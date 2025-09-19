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
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String[] data = parsePayload(payload);
            String latitude = data[0];
            String longitude = data[1];
            String date = data[2];

            String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getDouble("temperature");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -999.0; // Return a special value to indicate error or no data found
    }

    private String[] parsePayload(String payload) {
        return payload.split(",");
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temperature = service.temperature_for_location("37.7749,-122.4194,2023-10-01");
        System.out.println("Temperature: " + temperature);
    }
}