import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static double temperature_for_location(double latitude, double longitude, String date) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        double temperature = -999.0; // Default value indicating failure

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/weatherdb", "username", "password"
            );

            // Prepare the SQL query
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            // Execute the query and process the result set
            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                temperature = resultSet.getDouble("temperature");
            }

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            // Close resources in reverse order of their creation
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return temperature;
    }

    public static void main(String[] args) {
        double latitude = 37.7749;
        double longitude = -122.4194;
        String date = "2023-10-05";

        double temperature = temperature_for_location(latitude, longitude, date);
        System.out.println("Temperature: " + temperature);
    }
}