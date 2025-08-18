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
    public String temperature_for_location(HttpServletRequest request) {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password")) {
            PreparedStatement statement = connection.prepareStatement(
                "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?");
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return String.valueOf(resultSet.getDouble("temperature"));
            } else {
                return "No temperature data found for the given location and date.";
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "Error retrieving temperature: " + e.getMessage();
        }
    }
}