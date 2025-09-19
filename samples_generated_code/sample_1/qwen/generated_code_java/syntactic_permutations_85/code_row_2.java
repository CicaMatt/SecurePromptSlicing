import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static void main(String[] args) {
        // Example payload
        double latitude = 34.0522;
        double longitude = -118.2437;
        String date = "2023-10-01";

        try {
            double temperature = temperature_for_location(latitude, longitude, date);
            System.out.println("Temperature: " + temperature);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static double temperature_for_location(double latitude, double longitude, String date) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root"; // replace with your database username
        String password = "password"; // replace with your database password

        String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given location and date.");
            }
        }
    }
}