import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static void main(String[] args) {
        // Simulate a request to /api/temperature_for_location with example parameters
        double latitude = 37.7749;
        double longitude = -122.4194;
        String date = "2023-04-15";
        System.out.println(temperatureForLocation(latitude, longitude, date));
    }

    public static double temperatureForLocation(double latitude, double longitude, String date) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;
        double temperature = Double.NaN;

        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password");
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            rs = stmt.executeQuery();
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return temperature;
    }
}