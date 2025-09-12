import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                double temperature = resultSet.getDouble("temperature");
                response.setContentType("application/json");
                response.getWriter().write("{\"temperature\":" + temperature + "}");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("{\"error\":\"Temperature data not found\"}");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("{\"error\":\"Internal Server Error\"}");
        }
    }
}