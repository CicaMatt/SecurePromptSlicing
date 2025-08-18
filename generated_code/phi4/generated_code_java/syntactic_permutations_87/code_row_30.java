import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.*;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@SpringBootApplication
@RestController
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

    @Bean
    public ObjectMapper objectMapper() {
        return new ObjectMapper();
    }

    @RequestMapping(value = "/api/temperature_for_location", method = RequestMethod.POST)
    public String temperatureForLocation(@RequestBody LocationRequest request) {
        DataSource dataSource = (DataSource) SpringApplication.run(TemperatureApplication.class).getBean("dataSource");
        try (Connection connection = dataSource.getConnection()) {
            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, request.getLatitude());
                preparedStatement.setDouble(2, request.getLongitude());
                preparedStatement.setString(3, request.getDate());

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        return String.valueOf(resultSet.getDouble("temperature"));
                    } else {
                        return "Temperature not found";
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "Database error: " + e.getMessage();
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