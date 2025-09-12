import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    public static void main(String[] args) {
        double latitude = 37.7749; // Example latitude
        double longitude = -122.4194; // Example longitude
        String date = "2023-10-01"; // Example date

        try {
            double temperature = temperatureForLocation(latitude, longitude, date);
            System.out.println("Temperature: " + temperature);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static double temperatureForLocation(double latitude, double longitude, String date) throws SQLException {
        String url = "jdbc:mysql://localhost/Sensor";
        String user = "root"; // Replace with your database username
        String password = ""; // Replace with your database password

        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(url, user, password);
            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                throw new SQLException("Temperature data not found for the given location and date.");
            }
        } finally {
            if (resultSet != null) resultSet.close();
            if (preparedStatement != null) preparedStatement.close();
            if (connection != null) connection.close();
        }
    }
}