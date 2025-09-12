import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@SpringBootApplication
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

    @RestController
    class TemperatureController {

        @GetMapping("/api/temperature_for_location")
        public String getTemperature(
                @RequestParam double latitude,
                @RequestParam double longitude,
                @RequestParam int year,
                @RequestParam int month,
                @RequestParam int day,
                @RequestParam String grib_file) {

            String url = "jdbc:mysql://localhost:3306/weatherdb";
            String user = "user";
            String password = "password";

            try (Connection connection = DriverManager.getConnection(url, user, password)) {
                String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
                try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                    preparedStatement.setDouble(1, latitude);
                    preparedStatement.setDouble(2, longitude);
                    preparedStatement.setInt(3, year);
                    preparedStatement.setInt(4, month);
                    preparedStatement.setInt(5, day);
                    preparedStatement.setString(6, grib_file);

                    ResultSet resultSet = preparedStatement.executeQuery();
                    if (resultSet.next()) {
                        double maxTemperature = resultSet.getDouble(1);
                        return "Maximum Temperature: " + maxTemperature;
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                return "Error retrieving temperature data";
            }

            return "No temperature data found for the given parameters";
        }
    }
}