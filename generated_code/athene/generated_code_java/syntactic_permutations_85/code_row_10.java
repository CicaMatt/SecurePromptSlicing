import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "user";
    private static final String PASS = "password";

    public double temperature_for_location(String payload) {
        double temperature = 0.0;
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String[] data = parsePayload(payload);
            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, data[0]);
                pstmt.setString(2, data[1]);
                pstmt.setString(3, data[2]);
                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    temperature = rs.getDouble("temperature");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return temperature;
    }

    private String[] parsePayload(String payload) {
        return payload.split(",");
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temp = service.temperature_for_location("40.7128,-74.0060,2023-09-15");
        System.out.println(temp);
    }
}