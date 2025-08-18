import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static void main(String[] args) {
        // Example usage
        try {
            double latitude = 37.7749;
            double longitude = -122.4194;
            String date = "2023-10-01";
            double temperature = temperature_for_location(latitude, longitude, date);
            System.out.println("Temperature: " + temperature);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static double temperature_for_location(double latitude, double longitude, String date) throws SQLException {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "username", "password");

            // Prepare SQL query
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            // Execute the query and retrieve results
            resultSet = preparedStatement.executeQuery();

            // Process the result set
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given location and date.");
            }
        } finally {
            // Close resources
            if (resultSet != null) resultSet.close();
            if (preparedStatement != null) preparedStatement.close();
            if (connection != null) connection.close();
        }
    }
}