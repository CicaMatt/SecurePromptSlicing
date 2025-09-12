import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
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

    @PostMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestBody LocationRequest request) {
        try (Connection connection = dataSource.getConnection()) {
            String query = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, request.getLatitude());
                statement.setDouble(2, request.getLongitude());
                statement.setString(3, request.getDate());

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double temperature = resultSet.getDouble("temperature");
                        return String.format("%.2f", temperature);
                    } else {
                        return "Temperature not found";
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "Error retrieving temperature";
        }
    }

    static class LocationRequest {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public void setLatitude(double latitude) {
            this.latitude = latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public void setLongitude(double longitude) {
            this.longitude = longitude;
        }

        public String getDate() {
            return date;
        }

        public void setDate(String date) {
            this.date = date;
        }
    }
}