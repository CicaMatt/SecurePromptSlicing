import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api")
public class TemperatureController {

    @GetMapping("/temperature_for_location")
    public double temperature_for_location(HttpServletRequest request) {
        String latitude = request.getParameter("latitude");
        if (latitude == null || latitude.isEmpty()) {
            throw new IllegalArgumentException("Latitude is required.");
        }

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weather", "user", "password")) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, latitude);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getDouble("temperature");
                } else {
                    throw new RuntimeException("No data found for the given latitude.");
                }
            }
        } catch (Exception e) {
            throw new RuntimeException(e.getMessage(), e);
        }
    }
}