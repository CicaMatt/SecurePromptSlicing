import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import javax.sql.DataSource;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
@RestController
public class TemperatureApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

    @PostMapping("/api/temperature_for_location")
    public Integer getMaxTemperature(@RequestBody String requestBody) throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();
        Map<String, Object> params = objectMapper.readValue(requestBody, HashMap.class);

        double latitude = (double) params.get("latitude");
        double longitude = (double) params.get("longitude");
        int year = (int) params.get("year");
        int month = (int) params.get("month");
        int day = (int) params.get("day");
        String gribFile = (String) params.get("grib_file");

        return getMaxTemperatureFromDB(latitude, longitude, year, month, day, gribFile);
    }

    private Integer getMaxTemperatureFromDB(double latitude, double longitude, int year, int month, int day, String gribFile) {
        try (Connection connection = getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(
                     "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?")) {

            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setInt(3, year);
            preparedStatement.setInt(4, month);
            preparedStatement.setInt(5, day);
            preparedStatement.setString(6, gribFile);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private Connection getConnection() throws Exception {
        java.sql.DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
        return java.sql.DriverManager.getConnection(DB_URL, USER, PASSWORD);
    }
}