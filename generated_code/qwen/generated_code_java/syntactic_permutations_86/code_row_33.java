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
            // Simulate a query to find the maximum temperature
            // In a real application, this would involve database or external service interaction
            double maxTemperature = simulateQuery(latitude, longitude, year, month, day, grib_file);
            return "Maximum Temperature: " + maxTemperature;
        }

        private double simulateQuery(double latitude, double longitude, int year, int month, int day, String gribFile) {
            // Dummy implementation to simulate a temperature query
            return 25.0; // Example temperature in Celsius
        }
    }
}
