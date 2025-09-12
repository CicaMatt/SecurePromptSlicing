import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class TemperatureController {

    public void temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password")) {
            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                double temperature = resultSet.getDouble("temperature");
                response.getWriter().write(new JSONObject().put("temperature", temperature).toString());
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write(new JSONObject().put("error", "No data found for the given location and date").toString());
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            try {
                response.getWriter().write(new JSONObject().put("error", "Database error").toString());
            } catch (Exception ex) {
                // Handle exception
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            try {
                response.getWriter().write(new JSONObject().put("error", "Unknown error").toString());
            } catch (Exception ex) {
                // Handle exception
            }
        }
    }
}