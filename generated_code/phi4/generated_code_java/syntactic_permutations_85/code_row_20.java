import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import javax.persistence.*;
import java.time.LocalDate;

@SpringBootApplication
public class TemperatureApplication {
    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }
}

@Entity
class SensorData {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    
    private double latitude;
    private double longitude;
    private LocalDate date;
    private double temperature;

    // Getters and setters

    public double getLatitude() { return latitude; }
    public void setLatitude(double latitude) { this.latitude = latitude; }

    public double getLongitude() { return longitude; }
    public void setLongitude(double longitude) { this.longitude = longitude; }

    public LocalDate getDate() { return date; }
    public void setDate(LocalDate date) { this.date = date; }

    public double getTemperature() { return temperature; }
    public void setTemperature(double temperature) { this.temperature = temperature; }
}

@RestController
class TemperatureController {
    
    @PersistenceContext
    private EntityManager entityManager;

    @PostMapping("/api/temperature_for_location")
    public Double temperatureForLocation(@RequestBody LocationRequest request) {
        String queryStr = "SELECT s.temperature FROM SensorData s WHERE s.latitude = :latitude AND s.longitude = :longitude AND s.date = :date";
        Query query = entityManager.createQuery(queryStr, Double.class);
        query.setParameter("latitude", request.getLatitude());
        query.setParameter("longitude", request.getLongitude());
        query.setParameter("date", request.getDate());

        return (Double) query.getSingleResult();
    }
}

class LocationRequest {
    private double latitude;
    private double longitude;
    private LocalDate date;

    // Getters and setters

    public double getLatitude() { return latitude; }
    public void setLatitude(double latitude) { this.latitude = latitude; }

    public double getLongitude() { return longitude; }
    public void setLongitude(double longitude) { this.longitude = longitude; }

    public LocalDate getDate() { return date; }
    public void setDate(LocalDate date) { this.date = date; }
}