import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import org.json.JSONObject;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getReader().lines().reduce("", (accumulator, actual) -> accumulator + actual);
        JSONObject jsonPayload = new JSONObject(payload);

        double latitude = jsonPayload.getDouble("latitude");
        double longitude = jsonPayload.getDouble("longitude");
        String date = jsonPayload.getString("date");

        String temperature = getTemperatureFromDatabase(latitude, longitude, date);

        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\": \"" + temperature + "\"}");
    }

    private String getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String sql = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setString(3, date);

                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getString("temperature");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "N/A";
    }
}