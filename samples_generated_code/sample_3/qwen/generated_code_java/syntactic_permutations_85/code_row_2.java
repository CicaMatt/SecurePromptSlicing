import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static void main(String[] args) {
        // Example payload
        double latitude = 37.7749;
        double longitude = -122.4194;
        String date = "2023-10-01";

        try {
            double temperature = temperature_for_location(latitude, longitude, date);
            System.out.println("Temperature: " + temperature + "°C");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static double temperature_for_location(double latitude, double longitude, String date) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root"; // replace with your database username
        String password = ""; // replace with your database password

        String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given location and date.");
            }
        }
    }
}