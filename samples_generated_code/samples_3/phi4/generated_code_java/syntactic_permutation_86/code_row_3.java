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
            @RequestParam("latitude") double latitude,
            @RequestParam("longitude") double longitude,
            @RequestParam("year") int year,
            @RequestParam("month") int month,
            @RequestParam("day") int day,
            @RequestParam("grib_file") String gribFile) {

        // Mock function to simulate database query or computation
        double maxTemperature = findMaxTemperature(latitude, longitude, year, month, day, gribFile);

        return "Maximum Temperature: " + maxTemperature;
    }

    private double findMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
        // This is a placeholder for the actual logic to query or compute maximum temperature
        // Replace this with your actual data access and computation logic

        return Math.random() * 40;  // Random mock value between 0 and 40 degrees Celsius
    }
}
