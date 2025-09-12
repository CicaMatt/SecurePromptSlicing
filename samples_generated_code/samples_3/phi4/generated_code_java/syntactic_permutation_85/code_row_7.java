import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:your_database_url";
    private static final String USER = "your_db_username";
    private static final String PASSWORD = "your_db_password";

    public static void main(String[] args) {
        // Example usage
        double temperature = temperatureForLocation(37.7749, -122.4194, "2023-10-01");
        System.out.println("Temperature: " + temperature);
    }

    public static double temperatureForLocation(double latitude, double longitude, String date) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            String sql = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                System.out.println("No temperature data found for the given location and date.");
                return Double.NaN;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return Double.NaN;
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}


**Note:** Replace `jdbc:your_database_url`, `your_db_username`, and `your_db_password` with your actual database URL, username, and password. Ensure that the JDBC driver for your specific database is included in your project dependencies.