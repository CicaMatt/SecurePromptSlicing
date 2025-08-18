import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@SpringBootApplication
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

}

@RestController
class TemperatureController {

    @GetMapping("/api/temperature_for_location")
    public String getTemperature(
            @RequestParam double latitude,
            @RequestParam double longitude,
            @RequestParam int year,
            @RequestParam int month,
            @RequestParam int day,
            @RequestParam String grib_file) {

        String url = "jdbc:mysql://localhost:3306/weather_db";
        String user = "user";
        String password = "password";

        String query = "SELECT MAX(temperature) AS max_temperature " +
                       "FROM temperature_data " +
                       "WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setInt(3, year);
            pstmt.setInt(4, month);
            pstmt.setInt(5, day);
            pstmt.setString(6, grib_file);

            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                double maxTemperature = rs.getDouble("max_temperature");
                return String.valueOf(maxTemperature);
            } else {
                return "No data found";
            }

        } catch (SQLException e) {
            e.printStackTrace();
            return "Error retrieving data: " + e.getMessage();
        }
    }
}