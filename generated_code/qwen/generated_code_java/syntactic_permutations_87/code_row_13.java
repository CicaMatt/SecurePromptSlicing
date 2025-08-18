import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public double temperature_for_location(double latitude, double longitude, String date) throws SQLException {
        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                throw new SQLException("Temperature data not found for the given location and date.");
            }
        }
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        try {
            double temperature = service.temperature_for_location(34.0522, -118.2437, "2023-10-01");
            System.out.println("Temperature: " + temperature);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}