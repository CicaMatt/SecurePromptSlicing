import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

    @GetMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestParam double latitude,
                                         @RequestParam double longitude,
                                         @RequestParam String date) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "username";
        String password = "password";
        String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);
            
            ResultSet resultSet = preparedStatement.executeQuery();
            
            if (resultSet.next()) {
                return "Temperature: " + resultSet.getDouble("temperature");
            } else {
                return "No temperature data found for the specified location and date.";
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "Error fetching temperature data";
        }
    }
}