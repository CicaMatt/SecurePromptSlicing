import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    public double temperature_for_location(String latitude, String longitude, String date) {
        double temperature = 0.0;
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, latitude);
            pstmt.setString(2, longitude);
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
        double temp = service.temperature_for_location("37.7749", "-122.4194", "2023-10-05");
        System.out.println("Temperature: " + temp);
    }
}