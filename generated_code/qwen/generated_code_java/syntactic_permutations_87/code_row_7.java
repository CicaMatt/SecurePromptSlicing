import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public double temperature_for_location(double latitude, double longitude, String date) throws SQLException {
        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
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

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        try {
            double temperature = service.temperature_for_location(37.7749, -122.4194, "2023-10-01");
            System.out.println("Temperature: " + temperature);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}



<!-- Add this dependency to your pom.xml if using Maven -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>