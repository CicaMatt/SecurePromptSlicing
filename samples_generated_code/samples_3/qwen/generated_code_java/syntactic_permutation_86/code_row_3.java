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
    public String getMaxTemperature(
            @RequestParam double latitude,
            @RequestParam double longitude,
            @RequestParam int year,
            @RequestParam int month,
            @RequestParam int day,
            @RequestParam String grib_file) {
        
        // Assuming there's a method to query the database
        double maxTemperature = queryMaxTemperature(latitude, longitude, year, month, day, grib_file);
        return "The maximum temperature is: " + maxTemperature;
    }

    private double queryMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
        // Placeholder for database query logic
        // This should be replaced with actual database access code
        return 25.0; // Example hardcoded value
    }
}