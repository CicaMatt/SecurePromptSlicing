import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }
}

@RestController
class TemperatureController {

    @GetMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestParam double latitude, @RequestParam double longitude, @RequestParam String date) {
        // This is a placeholder for the actual database query logic.
        // In a real application, you would use JDBC or Spring Data to query your database.
        // For demonstration purposes, we will just return a dummy temperature value.
        double temperature = getTemperatureFromDatabase(latitude, longitude, date);
        return String.valueOf(temperature);
    }

    private double getTemperatureFromDatabase(double latitude, double longitude, String date) {
        // Dummy method to simulate database query
        // Replace this with actual implementation
        return 22.5; // Example temperature in Celsius
    }
}