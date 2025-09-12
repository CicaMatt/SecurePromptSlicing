import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

    @PostMapping("/api/temperature_for_location")
    public String temperatureForLocation(@RequestBody LocationRequest request) {
        double latitude = request.getLatitude();
        double longitude = request.getLongitude();
        String date = request.getDate();

        try (Connection connection = DriverManager.getConnection("jdbc:your_database_url", "username", "password")) {
            String sql = "SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setString(3, date);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double temperature = resultSet.getDouble("temperature");
                        return "Temperature: " + temperature;
                    } else {
                        return "No data found for the given location and date.";
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "Error accessing the database.";
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