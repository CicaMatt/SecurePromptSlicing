import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "username"; // replace with your database username
    private static final String PASS = "password"; // replace with your database password

    public double temperatureForLocation(double latitude, double longitude, String date) {
        double temperature = 0.0;
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setDouble(1, latitude);
                pstmt.setDouble(2, longitude);
                pstmt.setString(3, date);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        temperature = rs.getDouble("temperature");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return temperature;
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temp = service.temperatureForLocation(34.0522, -118.2437, "2023-10-01");
        System.out.println("Temperature: " + temp);
    }
}


Make sure to replace `"username"` and `"password"` with your actual database credentials. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.