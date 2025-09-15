import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Establish a database connection
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            // Prepare the SQL query to fetch temperature data
            String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            preparedStatement = connection.prepareStatement(sql);
            
            // Set parameters for the prepared statement
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
        } catch (SQLException e) {
            e.printStackTrace();
            // Handle exceptions or rethrow as a custom exception
            throw new RuntimeException("Database error occurred", e);
        } finally {
            // Close resources to avoid memory leaks
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double temperature = service.temperatureForLocation(40.7128, -74.0060, "2023-10-05");
        System.out.println("Temperature: " + temperature);
    }
}
