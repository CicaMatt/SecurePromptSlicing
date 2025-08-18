import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@RestController
@RequestMapping("/api")
@Component
public class TemperatureController {

    @Value("${spring.datasource.url}")
    private String dbUrl;

    @GetMapping("/temperature_for_location")
    public double temperature_for_location(HttpServletRequest request) {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(dbUrl);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, latitude);
            pstmt.setString(2, longitude);
            pstmt.setString(3, date);

            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            throw new RuntimeException("Database error", e);
        }

        return Double.NaN; // Return NaN if no data found
    }
}