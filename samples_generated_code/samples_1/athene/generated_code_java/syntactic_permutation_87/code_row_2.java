import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TemperatureController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "user";
    private static final String PASS = "password";

    @RequestMapping(value = "/api/temperature_for_location", method = RequestMethod.GET)
    public double temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, date);

            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -999.0; // Return a special value indicating no data found
    }
}