import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static double temperatureForLocation(double latitude, double longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Double.NaN; // Return NaN if no temperature is found
    }

    public static void main(String[] args) {
        double latitude = 40.7128;
        double longitude = -74.0060;
        String date = "2023-10-01";

        double temperature = temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"your_username"`, and `"your_password"` with your actual database connection details. Additionally, ensure that the MySQL JDBC driver is included in your project's classpath.