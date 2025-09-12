import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "user";
    private static final String PASS = "password";

    public double temperature_for_location(double latitude, double longitude, String date) {
        double temperature = 0.0;
        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                temperature = resultSet.getDouble("temperature");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return temperature;
    }
}