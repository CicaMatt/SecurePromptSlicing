import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static void main(String[] args) {
        // Example usage: Assuming you have a method to handle HTTP requests that calls this function.
        double temperature = temperatureForLocation(37.7749, -122.4194, "2023-10-01");
        System.out.println("Temperature: " + temperature);
    }

    public static double temperatureForLocation(double latitude, double longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "yourUsername"; // Replace with your database username
        String password = "yourPassword"; // Replace with your database password

        String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                System.out.println("No temperature data found for the given location and date.");
                return Double.NaN; // Return NaN or an appropriate value indicating no data
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return Double.NaN;
        }
    }
}


Make sure to replace `yourUsername` and `yourPassword` with your actual database credentials. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.