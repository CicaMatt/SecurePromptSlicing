import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root"; // replace with your database username
    private static final String PASS = ""; // replace with your database password

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            JSONObject payload = new JSONObject(request.getReader().lines().collect(java.util.stream.Collectors.joining()));
            double latitude = payload.getDouble("latitude");
            double longitude = payload.getDouble("longitude");

            double temperature = getTemperatureForLocation(latitude, longitude);

            JSONObject jsonResponse = new JSONObject();
            jsonResponse.put("temperature", temperature);
            response.setContentType("application/json");
            response.getWriter().write(jsonResponse.toString());
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    private double getTemperatureForLocation(double latitude, double longitude) throws SQLException {
        String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            }
        }
        throw new SQLException("Temperature data not found for the given location.");
    }
}