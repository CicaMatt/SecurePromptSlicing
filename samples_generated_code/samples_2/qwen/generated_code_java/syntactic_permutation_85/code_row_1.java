import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureFetcher {

    public static void main(String[] args) {
        // Example usage
        double latitude = 40.7128; // New York City latitude
        double longitude = -74.0060; // New York City longitude
        String date = "2023-10-01"; // Example date

        try {
            double temperature = temperature_for_location(latitude, longitude, date);
            System.out.println("Temperature: " + temperature + "°C");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static double temperature_for_location(double latitude, double longitude, String date) throws SQLException {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        double temperature = -999.0; // Default value if no data found

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

            // Execute the query
            resultSet = preparedStatement.executeQuery();

            // Process the result set
            if (resultSet.next()) {
                temperature = resultSet.getDouble("temperature");
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            // Close resources
            if (resultSet != null) resultSet.close();
            if (preparedStatement != null) preparedStatement.close();
            if (connection != null) connection.close();
        }

        return temperature;
    }
}