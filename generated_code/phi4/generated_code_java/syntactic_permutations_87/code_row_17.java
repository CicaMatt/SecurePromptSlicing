import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@SpringBootApplication
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }
}

@RestController
class TemperatureController {

    private final DataSource dataSource;

    public TemperatureController(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @GetMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestParam("latitude") double latitude) {
        try (Connection connection = dataSource.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(
                     "SELECT temperature FROM temperatures WHERE latitude = ?")) {

            preparedStatement.setDouble(1, latitude);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return String.valueOf(resultSet.getDouble("temperature"));
                } else {
                    return "Temperature not found for the given latitude.";
                }
            }

        } catch (Exception e) {
            return "Error retrieving temperature: " + e.getMessage();
        }
    }
}